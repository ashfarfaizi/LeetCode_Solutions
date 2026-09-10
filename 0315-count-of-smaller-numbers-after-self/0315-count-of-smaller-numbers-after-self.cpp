#include <vector>
#include <utility>

class Solution {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> counts(n, 0);
        std::vector<std::pair<int, int>> v(n);
        
        // Store the number and its original index
        for (int i = 0; i < n; ++i) {
            v[i] = {nums[i], i};
        }
        
        mergeSort(v, counts, 0, n - 1);
        return counts;
    }

private:
    void mergeSort(std::vector<std::pair<int, int>>& v, std::vector<int>& counts, int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(v, counts, left, mid);
        mergeSort(v, counts, mid + 1, right);
        merge(v, counts, left, mid, right);
    }

    void merge(std::vector<std::pair<int, int>>& v, std::vector<int>& counts, int left, int mid, int right) {
        std::vector<std::pair<int, int>> temp(right - left + 1);
        int i = left;      // Pointer for left half
        int j = mid + 1;   // Pointer for right half
        int k = 0;         // Pointer for temp array
        int right_less_count = 0; // Number of elements from right half smaller than left[i]

        while (i <= mid && j <= right) {
            if (v[j].first < v[i].first) {
                // Right element is smaller than left element
                right_less_count++;
                temp[k++] = v[j++];
            } else {
                // Left element is smaller or equal; commit accumulated counts
                counts[v[i].second] += right_less_count;
                temp[k++] = v[i++];
            }
        }

        // Clean up remaining left elements
        while (i <= mid) {
            counts[v[i].second] += right_less_count;
            temp[k++] = v[i++];
        }

        // Clean up remaining right elements
        while (j <= right) {
            temp[k++] = v[j++];
        }

        // Copy back to original array
        for (int p = 0; p < temp.size(); ++p) {
            v[left + p] = temp[p];
        }
    }
};
