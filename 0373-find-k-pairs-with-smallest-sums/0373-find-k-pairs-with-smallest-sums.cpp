class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty() || k == 0) return result;

        // Min-heap storing: {sum, index_in_nums1, index_in_nums2}
        // Using greater auto-arranges the smallest sum at top
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;

        // 1. Initialize the heap up to a threshold constraint of k
        int n1 = nums1.size();
        int n2 = nums2.size();
        for (int i = 0; i < min(n1, k); ++i) {
            minHeap.push({nums1[i] + nums2[0], i, 0});
        }

        // 2. Extract min element and look forward linearly along nums2
        while (k-- > 0 && !minHeap.empty()) {
            auto current = minHeap.top();
            minHeap.pop();

            int i = current[1];
            int j = current[2];

            result.push_back({nums1[i], nums2[j]});

            // If a next element exists inside nums2 for the current nums1[i] row
            if (j + 1 < n2) {
                minHeap.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }

        return result;
    }
};
