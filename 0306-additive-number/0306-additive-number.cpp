#include <string>
#include <algorithm>

class Solution {
public:
    bool isAdditiveNumber(std::string num) {
        int n = num.length();
        if (n < 3) return false;

        // i represents the end index of the first number
        for (int i = 0; i < n / 2; ++i) {
            // Leading zero check for the first number
            if (num[0] == '0' && i > 0) break; 
            
            std::string n1_str = num.substr(0, i + 1);

            // j represents the end index of the second number
            for (int j = i + 1; n - 1 - j >= std::max(i + 1, j - i); ++j) {
                // Leading zero check for the second number
                if (num[i + 1] == '0' && j > i + 1) break;

                std::string n2_str = num.substr(i + 1, j - i);

                // Recursively or iteratively verify if this pair forms a valid sequence
                if (isValid(n1_str, n2_str, j + 1, num)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool isValid(std::string n1, std::string n2, int k, const std::string& num) {
        if (k == num.length()) return true;

        std::string sum = addStrings(n1, n2);
        
        // If the remaining string doesn't start with the calculated sum, it's invalid
        if (num.compare(k, sum.length(), sum) != 0) {
            return false;
        }

        // Move to the next sequence item
        return isValid(n2, sum, k + sum.length(), num);
    }

    // Helper function to handle string addition and prevent integer overflow
    std::string addStrings(std::string num1, std::string num2) {
        std::string result = "";
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            carry = sum / 10;
            result += std::to_string(sum % 10);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
