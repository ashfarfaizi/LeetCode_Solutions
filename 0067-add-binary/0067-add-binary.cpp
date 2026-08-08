#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string result = "";
        int i = a.length() - 1;
        int j = b.length() - 1;
        int carry = 0;

        // Loop as long as there are digits left to add or a carry remaining
        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            // Extract digit from string a if index is within bounds
            if (i >= 0) {
                sum += a[i] - '0';
                i--;
            }

            // Extract digit from string b if index is within bounds
            if (j >= 0) {
                sum += b[j] - '0';
                j--;
            }

            // Append the binary digit to the result string
            result += to_string(sum % 2);

            // Compute the carry for the next significant bit position
            carry = sum / 2;
        }

        // The result was built backwards, reverse it to get correct order
        reverse(result.begin(), result.end());
        return result;
    }
};
