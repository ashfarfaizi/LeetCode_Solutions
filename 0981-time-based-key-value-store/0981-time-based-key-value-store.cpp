/*
 * Approach: per-key vector of (timestamp, value) pairs. Timestamps passed to
 * set() are strictly increasing, so each vector stays sorted and set() is a
 * push_back. get() binary-searches for the first timestamp greater than the
 * query and steps back one to find the latest entry at or before it.
 *
 * Time:  set O(1) amortised, get O(log m) for m entries under the key
 * Space: O(total entries)
 */
class TimeMap {
public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        store[key].emplace_back(timestamp, value);
    }

    string get(string key, int timestamp) {
        auto it = store.find(key);
        if (it == store.end()) return "";
        const auto& entries = it->second;
        auto pos = upper_bound(entries.begin(), entries.end(), timestamp,
                               [](int t, const pair<int, string>& e) { return t < e.first; });
        return pos == entries.begin() ? "" : prev(pos)->second;
    }

private:
    unordered_map<string, vector<pair<int, string>>> store;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
