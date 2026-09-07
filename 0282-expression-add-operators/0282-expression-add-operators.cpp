#include <vector>
#include <string>

class Solution {
private:
    std::vector<std::string> result;
    std::string numStr;
    long long targetVal;

    void backtrack(int index, std::string path, long long currentEvaluation, long long prevOperand) {
        // Base case: If we've processed all digits
        if (index == numStr.length()) {
            if (currentEvaluation == targetVal) {
                result.push_back(path);
            }
            return;
        }

        // Try extracting operands of varying lengths
        for (int i = index; i < numStr.length(); ++i) {
            // Corner Case: Leading zero numbers (e.g., "05" is invalid, but "0" alone is valid)
            if (i > index && numStr[index] == '0') {
                break; 
            }

            std::string part = numStr.substr(index, i - index + 1);
            long long curr = std::stoll(part);

            // If it's the very first number, we cannot place an operator before it
            if (index == 0) {
                backtrack(i + 1, part, curr, curr);
            } else {
                // Option 1: Addition '+'
                backtrack(i + 1, path + "+" + part, currentEvaluation + curr, curr);

                // Option 2: Subtraction '-'
                backtrack(i + 1, path + "-" + part, currentEvaluation - curr, -curr);

                // Option 3: Multiplication '*'
                // Undo the previous operand addition/subtraction and scale it up
                backtrack(i + 1, path + "*" + part, currentEvaluation - prevOperand + (prevOperand * curr), prevOperand * curr);
            }
        }
    }

public:
    std::vector<std::string> addOperators(std::string num, int target) {
        result.clear();
        numStr = num;
        targetVal = target;
        
        if (num.empty()) return result;
        
        backtrack(0, "", 0, 0);
        return result;
    }
};
