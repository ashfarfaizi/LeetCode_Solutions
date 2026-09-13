#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int first = INT_MAX;
        int second = INT_MAX;
        
        for (int num : nums) {
            if (num <= first) {
                first = num;      // Find the smallest element so far
            } else if (num <= second) {
                second = num;     // Find the second smallest element so far
            } else {
                return true;      // Found a number greater than both first and second
            }
        }
        
        return false;
    }
};
