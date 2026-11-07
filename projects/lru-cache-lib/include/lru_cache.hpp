#pragma once
// Header-only, fixed-capacity LRU cache.
//
// Entries live in a std::list ordered from most to least recently used, and an
// unordered_map points from each key to its list node, so get() and put() are
// O(1) on average.

#include <cstddef>
#include <functional>
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lru {

// Counters describing how well the cache is doing.
struct Stats {
    std::size_t hits = 0;
    std::size_t misses = 0;
    std::size_t evictions = 0;

    double hitRate() const {
        std::size_t total = hits + misses;
        return total == 0 ? 0.0 : static_cast<double>(hits) / static_cast<double>(total);
    }
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class LRUCache {
public:
    // Called with the key and value of each entry evicted for capacity
    // (not for erase() or clear()).
    using EvictionCallback = std::function<void(const Key&, const Value&)>;

    explicit LRUCache(std::size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0) throw std::invalid_argument("LRUCache capacity must be > 0");
    }

    LRUCache(std::size_t capacity, EvictionCallback onEvict) : LRUCache(capacity) {
        onEvict_ = std::move(onEvict);
    }

    void setEvictionCallback(EvictionCallback onEvict) { onEvict_ = std::move(onEvict); }

    // Returns the value for key and marks it most recently used.
    std::optional<Value> get(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) {
            ++stats_.misses;
            return std::nullopt;
        }
        ++stats_.hits;
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }

    // Inserts or overwrites key; evicts the least recently used entry if full.
    void put(const Key& key, Value value) {
        auto it = index_.find(key);
        if (it != index_.end()) {
            it->second->second = std::move(value);
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        if (items_.size() == capacity_) evictLeastRecent();
        items_.emplace_front(key, std::move(value));
        index_[key] = items_.begin();
    }

    // True if key is cached; does not change recency.
    bool contains(const Key& key) const { return index_.count(key) != 0; }

    // Returns the value for key without marking it as recently used.
    std::optional<Value> peek(const Key& key) const {
        auto it = index_.find(key);
        if (it == index_.end()) return std::nullopt;
        return it->second->second;
    }

    // Removes key if present; returns whether anything was removed.
    bool erase(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) return false;
        items_.erase(it->second);
        index_.erase(it);
        return true;
    }

    // Changes the capacity. Shrinking below size() evicts least recently used
    // entries (counted in stats and passed to the eviction callback).
    void resize(std::size_t newCapacity) {
        if (newCapacity == 0) throw std::invalid_argument("LRUCache capacity must be > 0");
        capacity_ = newCapacity;
        while (items_.size() > capacity_) evictLeastRecent();
    }

    void clear() {
        items_.clear();
        index_.clear();
    }

    // Visits entries from most to least recently used without changing
    // recency. fn receives (const Key&, const Value&) and must not modify the
    // cache.
    template <typename Fn>
    void forEach(Fn fn) const {
        for (const Entry& e : items_) fn(e.first, e.second);
    }

    // Keys ordered from most to least recently used.
    std::vector<Key> keys() const {
        std::vector<Key> out;
        out.reserve(items_.size());
        for (const Entry& e : items_) out.push_back(e.first);
        return out;
    }

    // Hit/miss counts come from get() only; peek() and contains() are not counted.
    const Stats& stats() const { return stats_; }
    void resetStats() { stats_ = Stats{}; }

    bool empty() const { return items_.empty(); }
    std::size_t size() const { return items_.size(); }
    std::size_t capacity() const { return capacity_; }

private:
    using Entry = std::pair<Key, Value>;

    void evictLeastRecent() {
        Entry victim = std::move(items_.back());
        index_.erase(victim.first);
        items_.pop_back();
        ++stats_.evictions;
        if (onEvict_) onEvict_(victim.first, victim.second);
    }

    std::size_t capacity_;
    Stats stats_;
    EvictionCallback onEvict_;
    std::list<Entry> items_;
    std::unordered_map<Key, typename std::list<Entry>::iterator, Hash> index_;
};

}  // namespace lru
