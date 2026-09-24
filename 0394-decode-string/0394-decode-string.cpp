#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;
        stack<string> stringStack;
        string currentString = "";
        int currentK = 0;
        
        for (char c : s) {
            if (isdigit(c)) {
                // Formulate the multi-digit repeat number
                currentK = currentK * 10 + (c - '0');
            } 
            else if (c == '[') {
                // Push the current state onto the stacks
                countStack.push(currentK);
                stringStack.push(currentString);
                
                // Reset states for processing the bracket contents
                currentString = "";
                currentK = 0;
            } 
            else if (c == ']') {
                // Reconstruct the inner string segment
                string decodedString = stringStack.top();
                stringStack.pop();
                
                int repeatTimes = countStack.top();
                countStack.pop();
                
                // Append the repeated current block to the previously saved context
                for (int i = 0; i < repeatTimes; i++) {
                    decodedString += currentString;
                }
                
                currentString = decodedString;
            } 
            else {
                // Append any normal alphabetic character to the current active segment
                currentString += c;
            }
        }
        
        return currentString;
    }
};
