#pragma once
// Header-only, fixed-capacity LFU (least frequently used) cache.
//
// Each entry carries a use count. Entries with the same count live in one
// std::list ordered from most to least recently used, so ties are broken by
// recency (the least recently used of the least frequently used entries is
// evicted). A map from key to list node plus the current minimum count keep
// get() and put() O(1) on average.

#include "lru_cache.hpp"  // for lru::Stats

#include <cstddef>
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace lru {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class LFUCache {
public:
    explicit LFUCache(std::size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0) throw std::invalid_argument("LFUCache capacity must be > 0");
    }

    // Returns the value and bumps its use count, or nullopt on a miss.
    std::optional<Value> get(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) {
            ++stats_.misses;
            return std::nullopt;
        }
        ++stats_.hits;
        touch(it->second);
        return it->second.node->value;
    }

    // Inserts or overwrites key. Overwriting counts as a use. Inserting into a
    // full cache first evicts the least frequently used entry.
    void put(const Key& key, Value value) {
        auto it = index_.find(key);
        if (it != index_.end()) {
            it->second.node->value = std::move(value);
            touch(it->second);
            return;
        }
        if (index_.size() == capacity_) evictOne();
        auto& bucket = buckets_[1];
        bucket.push_front(Node{key, std::move(value)});
        index_.emplace(key, Entry{1, bucket.begin()});
        minFreq_ = 1;
    }

    // Use count of key (0 if absent). Does not count as a use.
    std::size_t frequency(const Key& key) const {
        auto it = index_.find(key);
        return it == index_.end() ? 0 : it->second.freq;
    }

    bool contains(const Key& key) const { return index_.count(key) > 0; }

    bool erase(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) return false;
        removeFromBucket(it->second);
        index_.erase(it);
        return true;
    }

    void clear() {
        index_.clear();
        buckets_.clear();
        minFreq_ = 0;
    }

    std::size_t size() const { return index_.size(); }
    bool empty() const { return index_.empty(); }
    std::size_t capacity() const { return capacity_; }
    const Stats& stats() const { return stats_; }
    void resetStats() { stats_ = Stats{}; }

private:
    struct Node {
        Key key;
        Value value;
    };
    using Bucket = std::list<Node>;
    struct Entry {
        std::size_t freq;
        typename Bucket::iterator node;
    };

    // Moves the entry to the front of the next-higher frequency bucket.
    void touch(Entry& e) {
        Bucket& from = buckets_[e.freq];
        Bucket& to = buckets_[e.freq + 1];
        to.splice(to.begin(), from, e.node);
        if (from.empty()) {
            buckets_.erase(e.freq);
            if (minFreq_ == e.freq) ++minFreq_;
        }
        ++e.freq;
    }

    void removeFromBucket(const Entry& e) {
        auto b = buckets_.find(e.freq);
        b->second.erase(e.node);
        if (b->second.empty()) {
            buckets_.erase(b);
            if (minFreq_ == e.freq) recomputeMinFreq();
        }
    }

    void recomputeMinFreq() {
        minFreq_ = 0;
        for (const auto& [f, _] : buckets_)
            if (minFreq_ == 0 || f < minFreq_) minFreq_ = f;
    }

    void evictOne() {
        Bucket& b = buckets_[minFreq_];
        index_.erase(b.back().key);
        b.pop_back();
        if (b.empty()) buckets_.erase(minFreq_);
        ++stats_.evictions;
        // put() resets minFreq_ to 1 immediately after evicting.
    }

    std::size_t capacity_;
    std::size_t minFreq_ = 0;
    std::unordered_map<Key, Entry, Hash> index_;
    std::unordered_map<std::size_t, Bucket> buckets_;
    Stats stats_;
};

}  // namespace lru
