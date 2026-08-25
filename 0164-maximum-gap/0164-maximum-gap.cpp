#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int maximumGap(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;

        // Step 1: Find global min and max
        int min_val = nums[0];
        int max_val = nums[0];
        for (int num : nums) {
            min_val = std::min(min_val, num);
            max_val = std::max(max_val, num);
        }

        if (min_val == max_val) return 0; // All elements are identical

        // Step 2: Calculate bucket capacity size and count
        int bucket_size = std::max(1, (max_val - min_val) / (n - 1));
        int bucket_count = (max_val - min_val) / bucket_size + 1;

        // Step 3: Initialize tracking arrays for buckets
        std::vector<int> bucket_min(bucket_count, INT_MAX);
        std::vector<int> bucket_max(bucket_count, INT_MIN);

        // Step 4: Map values to respective buckets
        for (int num : nums) {
            int idx = (num - min_val) / bucket_size;
            bucket_min[idx] = std::min(bucket_min[idx], num);
            bucket_max[idx] = std::max(bucket_max[idx], num);
        }

        // Step 5: Compute max gap by checking boundaries across adjacent non-empty buckets
        int max_gap = 0;
        int previous_max = min_val;

        for (int i = 0; i < bucket_count; ++i) {
            // Skip empty buckets
            if (bucket_min[i] == INT_MAX) continue;

            // Gap is the difference between current bucket min and previous bucket max
            max_gap = std::max(max_gap, bucket_min[i] - previous_max);
            previous_max = bucket_max[i];
        }

        return max_gap;
    }
};
