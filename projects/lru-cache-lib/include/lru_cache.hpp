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

namespace lru {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class LRUCache {
public:
    explicit LRUCache(std::size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0) throw std::invalid_argument("LRUCache capacity must be > 0");
    }

    // Returns the value for key and marks it most recently used.
    std::optional<Value> get(const Key& key) {
        auto it = index_.find(key);
        if (it == index_.end()) return std::nullopt;
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
        if (items_.size() == capacity_) {
            index_.erase(items_.back().first);
            items_.pop_back();
        }
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

    void clear() {
        items_.clear();
        index_.clear();
    }

    bool empty() const { return items_.empty(); }
    std::size_t size() const { return items_.size(); }
    std::size_t capacity() const { return capacity_; }

private:
    using Entry = std::pair<Key, Value>;
    std::size_t capacity_;
    std::list<Entry> items_;
    std::unordered_map<Key, typename std::list<Entry>::iterator, Hash> index_;
};

}  // namespace lru
