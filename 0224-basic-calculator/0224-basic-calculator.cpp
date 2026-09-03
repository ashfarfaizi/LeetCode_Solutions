#include <string>
#include <stack>
#include <cctype>

class Solution {
public:
    int calculate(std::string s) {
        std::stack<int> st;
        int result = 0;
        long long number = 0; // Changed to long long to prevent signed integer overflow
        int sign = 1;         // 1 means (+), -1 means (-)

        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];

            if (isdigit(c)) {
                // Safely build the number using a 64-bit container
                number = number * 10 + (c - '0');
            } 
            else if (c == '+') {
                result += sign * number;
                number = 0;
                sign = 1;
            } 
            else if (c == '-') {
                result += sign * number;
                number = 0;
                sign = -1;
            } 
            else if (c == '(') {
                // Push the current running state to context stack
                st.push(result);
                st.push(sign);
                // Reset states for the internal nested scope
                result = 0;
                sign = 1;
            } 
            else if (c == ')') {
                result += sign * number;
                number = 0;
                
                // Resolve the brackets scope with the parent context
                result *= st.top(); 
                st.pop();
                result += st.top(); 
                st.pop();
            }
        }
        
        // Accumulate any remaining trailing operand
        result += sign * number;
        return result;
    }
};
