class Solution {
public:
    string frequencySort(string s) {
        int n = s.length();
        unordered_map<char, int> counts;
        
        // Step 1: Count frequencies of each character
        for (char c : s) {
            counts[c]++;
        }
        
        // Step 2: Create buckets where bucket[i] holds characters with frequency 'i'
        // Index goes from 0 to n, so size is n + 1
        vector<vector<char>> buckets(n + 1);
        for (auto& p : counts) {
            buckets[p.second].push_back(p.first);
        }
        
        // Step 3: Build the result string from the highest frequency bucket to the lowest
        string result = "";
        for (int i = n; i >= 1; --i) {
            if (!buckets[i].empty()) {
                for (char c : buckets[i]) {
                    // Append character 'c' repeated 'i' times
                    result.append(i, c);
                }
            }
        }
        
        return result;
    }
};
