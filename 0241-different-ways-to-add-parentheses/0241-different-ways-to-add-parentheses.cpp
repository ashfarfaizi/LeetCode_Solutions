#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

class Solution {
private:
    // Memoization table to cache results for substrings we've already computed
    std::unordered_map<std::string, std::vector<int>> memo;

public:
    std::vector<int> diffWaysToCompute(std::string expression) {
        // If we have already solved this sub-expression, return the cached result
        if (memo.find(expression) != memo.end()) {
            return memo[expression];
        }

        std::vector<int> results;

        // Iterate through the expression to find operators
        for (int i = 0; i < expression.length(); ++i) {
            char c = expression[i];

            if (c == '+' || c == '-' || c == '*') {
                // Split the expression into left and right sub-expressions around the operator
                std::string leftPart = expression.substr(0, i);
                std::string rightPart = expression.substr(i + 1);

                // Recursively solve for both halves
                std::vector<int> leftResults = diffWaysToCompute(leftPart);
                std::vector<int> rightResults = diffWaysToCompute(rightPart);

                // Combine the results from both halves using the current operator
                for (int l : leftResults) {
                    for (int r : rightResults) {
                        if (c == '+') {
                            results.push_back(l + r);
                        } else if (c == '-') {
                            results.push_back(l - r);
                        } else if (c == '*') {
                            results.push_back(l * r);
                        }
                    }
                }
            }
        }

        // Base case: If the expression contains no operators, it's just a raw number
        if (results.empty()) {
            results.push_back(std::stoi(expression));
        }

        // Cache the final results for this sub-expression scope
        memo[expression] = results;
        return results;
    }
};
