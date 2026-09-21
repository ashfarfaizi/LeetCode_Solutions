#include <vector>
#include <cstdlib>

class Solution {
private:
    std::vector<int> original;
    std::vector<int> shuffled;

public:
    Solution(std::vector<int>& nums) {
        original = nums;
        shuffled = nums;
    }
    
    std::vector<int> reset() {
        shuffled = original;
        return shuffled;
    }
    
    std::vector<int> shuffle() {
        int n = shuffled.size();
        for (int i = n - 1; i > 0; --i) {
            // Pick a random index from 0 to i
            int j = rand() % (i + 1);
            // Swap the element at the current index with the random index
            std::swap(shuffled[i], shuffled[j]);
        }
        return shuffled;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
