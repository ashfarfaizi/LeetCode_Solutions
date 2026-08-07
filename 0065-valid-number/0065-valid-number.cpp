#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExponent = false;
        bool digitAfterExponent = true;

        for (int i = 0; i < s.length(); ++i) {
            char ch = s[i];

            if (isdigit(ch)) {
                seenDigit = true;
                if (seenExponent) {
                    digitAfterExponent = true;
                }
            } 
            else if (ch == '+' || ch == '-') {
                // Signs are only allowed at the beginning or right after an exponent 'e'/'E'
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } 
            else if (ch == 'e' || ch == 'E') {
                // Exponent is only allowed if we've seen a digit before it, and no prior exponent exists
                if (seenExponent || !seenDigit) {
                    return false;
                }
                seenExponent = true;
                digitAfterExponent = false; // Must be validated by a digit coming after it
            } 
            else if (ch == '.') {
                // A decimal point cannot appear twice, or anywhere after an exponent 'e'/'E'
                if (seenDot || seenExponent) {
                    return false;
                }
                seenDot = true;
            } 
            else {
                // Any other characters (alphabets, spaces, symbols) are invalid
                return false;
            }
        }

        // The number is valid if we have seen at least one digit and any exponent block is filled
        return seenDigit && digitAfterExponent;
    }
};
