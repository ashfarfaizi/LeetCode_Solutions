class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        // Use long long to prevent integer overflow during prefix summation
        vector<long long> prefix_sums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }
        
        return mergeSortCount(prefix_sums, 0, n, lower, upper);
    }

private:
    int mergeSortCount(vector<long long>& sums, int start, int end, int lower, int upper) {
        if (end <= start) return 0;
        
        int mid = start + (end - start) / 2;
        // Count pairs localized entirely within the left or right halves
        int count = mergeSortCount(sums, start, mid, lower, upper) + 
                    mergeSortCount(sums, mid + 1, end, lower, upper);
        
        // Count split pairs crossing the boundary between left and right halves
        int low_ptr = mid + 1;
        int high_ptr = mid + 1;
        
        for (int i = start; i <= mid; ++i) {
            // Find the first index where sums[low_ptr] - sums[i] >= lower
            while (low_ptr <= end && sums[low_ptr] - sums[i] < lower) {
                low_ptr++;
            }
            // Find the first index where sums[high_ptr] - sums[i] > upper
            while (high_ptr <= end && sums[high_ptr] - sums[i] <= upper) {
                high_ptr++;
            }
            // All indices from low_ptr up to high_ptr - 1 are valid matches for sums[i]
            count += (high_ptr - low_ptr);
        }
        
        // Standard merge step to keep the array sorted for upper levels of recursion
        inplace_merge(sums.begin() + start, sums.begin() + mid + 1, sums.begin() + end + 1);
        
        return count;
    }
};
