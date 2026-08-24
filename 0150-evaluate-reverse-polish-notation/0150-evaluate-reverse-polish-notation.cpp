#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            // Check if the token is an operator
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // The first popped element is the right operand
                int num2 = st.top(); 
                st.pop();
                
                // The second popped element is the left operand
                int num1 = st.top(); 
                st.pop();
                
                // Apply the respective operator
                if (token == "+") st.push(num1 + num2);
                else if (token == "-") st.push(num1 - num2);
                else if (token == "*") st.push(num1 * num2);
                else if (token == "/") st.push(num1 / num2); // C++ division naturally truncates toward zero
            } else {
                // If the token is a number string, convert to int and push
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
};
