class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        unordered_map<int, int> countMap;
        for (int num : nums) {
            countMap[num]++;
        }
        
        // Step 2: Create buckets where index = frequency
        // The maximum possible frequency is nums.size()
        int n = nums.size();
        vector<vector<int>> buckets(n + 1);
        for (auto& [num, freq] : countMap) {
            buckets[freq].push_back(num);
        }
        
        // Step 3: Gather the top k frequent elements from right to left
        vector<int> result;
        for (int i = n; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) {
                    break;
                }
            }
        }
        
        return result;
    }
};
