#include <vector>
#include <queue>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // Create a min-heap (smallest element sits at the top)
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        // Iterate through all numbers in the array
        for (int num : nums) {
            min_heap.push(num);
            
            // If the heap grows larger than k, remove the smallest element
            if (min_heap.size() > k) {
                min_heap.pop();
            }
        }

        // The top of the heap is the kth largest element
        return min_heap.top();
    }
};
