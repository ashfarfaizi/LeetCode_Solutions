/*
 * Approach: Count words in a hash map, then keep a min-heap of size k
 * ordered so the "worst" word (lower count, or lexicographically larger on a
 * tie) sits on top and is evicted first. Pop the heap and reverse.
 * Time: O(n log k), Space: O(n)
 */
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for (const string& w : words) ++freq[w];

        auto better = [](const pair<int, string>& a, const pair<int, string>& b) {
            return a.first != b.first ? a.first > b.first : a.second < b.second;
        };
        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(better)> heap(better);
        for (auto& [w, c] : freq) {
            heap.push({c, w});
            if ((int)heap.size() > k) heap.pop();
        }

        vector<string> result;
        while (!heap.empty()) {
            result.push_back(heap.top().second);
            heap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
