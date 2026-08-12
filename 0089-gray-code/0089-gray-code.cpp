#include <vector>

class Solution {
public:
    std::vector<int> grayCode(int n) {
        std::vector<int> result;
        // Total number of elements in an n-bit Gray code sequence is 2^n
        int totalElements = 1 << n;
        result.reserve(totalElements);
        
        // Generate each Gray code using the bitwise formula: i ^ (i >> 1)
        for (int i = 0; i < totalElements; ++i) {
            result.push_back(i ^ (i >> 1));
        }
        
        return result;
    }
};
