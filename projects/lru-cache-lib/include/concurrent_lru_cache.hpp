#pragma once
// Thread-safe wrapper around lru::LRUCache.
//
// Every operation takes one mutex. get() reorders the recency list, so even
// reads need exclusive access; a shared_mutex would not help here.

#include "lru_cache.hpp"

#include <mutex>

namespace lru {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ConcurrentLRUCache {
public:
    explicit ConcurrentLRUCache(std::size_t capacity) : cache_(capacity) {}

    std::optional<Value> get(const Key& key) {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.get(key);
    }

    void put(const Key& key, Value value) {
        std::lock_guard<std::mutex> lock(mu_);
        cache_.put(key, std::move(value));
    }

    // Returns the cached value, or computes it with make(), stores and returns
    // it. make() runs outside the lock, so two threads may both compute a value
    // for the same missing key; the later put wins.
    template <typename Factory>
    Value getOrCompute(const Key& key, Factory make) {
        if (auto v = get(key)) return *v;
        Value v = make();
        put(key, v);
        return v;
    }

    std::optional<Value> peek(const Key& key) const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.peek(key);
    }

    bool contains(const Key& key) const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.contains(key);
    }

    void resize(std::size_t newCapacity) {
        std::lock_guard<std::mutex> lock(mu_);
        cache_.resize(newCapacity);
    }

    bool erase(const Key& key) {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.erase(key);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mu_);
        cache_.clear();
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.size();
    }

    std::size_t capacity() const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.capacity();
    }

    // Snapshot of the keys from most to least recently used.
    std::vector<Key> keys() const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.keys();
    }

    Stats stats() const {
        std::lock_guard<std::mutex> lock(mu_);
        return cache_.stats();
    }

    void resetStats() {
        std::lock_guard<std::mutex> lock(mu_);
        cache_.resetStats();
    }

private:
    mutable std::mutex mu_;
    LRUCache<Key, Value, Hash> cache_;
};

}  // namespace lru
