#pragma once
// LRU cache whose entries also expire a fixed time after they were written.
//
// Expired entries are dropped lazily: a lookup that finds one removes it and
// reports a miss, and purgeExpired() sweeps the whole cache on demand. The
// clock is a template parameter so tests can drive time by hand.

#include "lru_cache.hpp"

#include <chrono>

namespace lru {

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Clock = std::chrono::steady_clock>
class TTLLRUCache {
public:
    using Duration = typename Clock::duration;
    using TimePoint = typename Clock::time_point;

    TTLLRUCache(std::size_t capacity, Duration ttl) : cache_(capacity), ttl_(ttl) {
        if (ttl_ <= Duration::zero()) throw std::invalid_argument("TTLLRUCache ttl must be > 0");
    }

    // Returns the value if present and not expired; marks it most recently
    // used. Expired entries are removed and count as a miss.
    std::optional<Value> get(const Key& key) {
        if (const Slot* s = cache_.peekPtr(key); s && expired(*s)) cache_.erase(key);
        auto slot = cache_.get(key);
        if (!slot) return std::nullopt;
        return std::move(slot->value);
    }

    // Inserts or overwrites key; the entry expires ttl after this call.
    void put(const Key& key, Value value) {
        cache_.put(key, Slot{std::move(value), Clock::now() + ttl_});
    }

    // True if key is present and not expired. Does not change recency.
    bool contains(const Key& key) const {
        const Slot* s = cache_.peekPtr(key);
        return s && !expired(*s);
    }

    bool erase(const Key& key) { return cache_.erase(key); }
    void clear() { cache_.clear(); }

    // Removes every expired entry and returns how many were removed.
    std::size_t purgeExpired() {
        std::vector<Key> dead;
        cache_.forEach([&](const Key& k, const Slot& s) {
            if (expired(s)) dead.push_back(k);
        });
        for (const Key& k : dead) cache_.erase(k);
        return dead.size();
    }

    // Number of stored entries, including expired ones not yet purged.
    std::size_t size() const { return cache_.size(); }
    std::size_t capacity() const { return cache_.capacity(); }
    Duration ttl() const { return ttl_; }
    const Stats& stats() const { return cache_.stats(); }

private:
    struct Slot {
        Value value;
        TimePoint expiresAt;
    };

    static bool expired(const Slot& s) { return Clock::now() >= s.expiresAt; }

    LRUCache<Key, Slot, Hash> cache_;
    Duration ttl_;
};

}  // namespace lru
