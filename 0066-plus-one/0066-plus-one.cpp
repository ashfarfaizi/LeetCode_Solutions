#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        
        // Traverse the digits array from right to left
        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits; // No carry over needed, return early
            }
            // If the digit is 9, it becomes 0 due to carry over
            digits[i] = 0;
        }
        
        // If all digits were 9, we need an extra leading 1 (e.g., 99 -> 100)
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
