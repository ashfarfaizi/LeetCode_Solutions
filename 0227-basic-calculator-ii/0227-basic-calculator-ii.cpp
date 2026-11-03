/*
 * Approach: Single pass keeping a running sum and the value of the last
 * additive term. When an operator ends a number: + and - commit the last
 * term to the sum and start a new one; * and / fold the number into the last
 * term so higher precedence is respected without a stack.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int calculate(string s) {
        long sum = 0, last = 0, num = 0;
        char op = '+';
        for (size_t i = 0; i <= s.size(); ++i) {
            char c = i < s.size() ? s[i] : '+';
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c != ' ') {
                if (op == '+' || op == '-') {
                    sum += last;
                    last = op == '+' ? num : -num;
                } else if (op == '*') {
                    last *= num;
                } else {
                    last /= num;
                }
                op = c;
                num = 0;
            }
        }
        return static_cast<int>(sum + last);
    }
};
