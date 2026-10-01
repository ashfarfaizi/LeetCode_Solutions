#include <vector>
#include <climits>

class Solution {
public:
    int thirdMax(std::vector<int>& nums) {
        // Use long long pointers to comfortably handle INT_MIN boundary values
        long long first = LLONG_MIN;
        long long second = LLONG_MIN;
        long long third = LLONG_MIN;
        
        for (int num : nums) {
            // Skip duplicates to ensure distinct maximums
            if (num == first || num == second || num == third) {
                continue;
            }
            
            // Shift values down as a new maximum is found
            if (num > first) {
                third = second;
                second = first;
                first = num;
            } else if (num > second) {
                third = second;
                second = num;
            } else if (num > third) {
                third = num;
            }
        }
        
        // If third maximum wasn't updated, return the absolute maximum
        return (third == LLONG_MIN) ? first : third;
    }
};
