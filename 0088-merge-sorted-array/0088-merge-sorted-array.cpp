#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;         // Pointer for the last valid element in nums1
        int j = n - 1;         // Pointer for the last element in nums2
        int p = m + n - 1;     // Write pointer at the end of nums1

        // Merge elements from right to left (largest to smallest)
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[p] = nums1[i];
                i--;
            } else {
                nums1[p] = nums2[j];
                j--;
            }
            p--;
        }

        // If elements remain in nums2, copy them over
        // (Elements remaining in nums1 are already in their correct places)
        while (j >= 0) {
            nums1[p] = nums2[j];
            j--;
            p--;
        }
    }
};
