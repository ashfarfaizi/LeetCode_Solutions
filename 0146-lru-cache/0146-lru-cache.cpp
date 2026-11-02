/*
 * Approach: Doubly linked list (std::list) keeps keys in recency order, with
 * the most recent at the front; a hash map stores key -> list iterator so
 * get/put can splice a node to the front in O(1). Evict from the back when
 * capacity is exceeded.
 * Time: O(1) per op, Space: O(capacity)
 */
class LRUCache {
    int cap;
    list<pair<int, int>> items;  // {key, value}, front = most recent
    unordered_map<int, list<pair<int, int>>::iterator> pos;
public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        items.splice(items.begin(), items, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }
        if ((int)items.size() == cap) {
            pos.erase(items.back().first);
            items.pop_back();
        }
        items.emplace_front(key, value);
        pos[key] = items.begin();
    }
};
