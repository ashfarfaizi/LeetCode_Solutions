#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

class Solution {
private:
    // Helper function to check if a string has valid parentheses
    bool isValid(const std::string& str) {
        int count = 0;
        for (char ch : str) {
            if (ch == '(') {
                count++;
            } else if (ch == ')') {
                count--;
                if (count < 0) return false; 
            }
        }
        return count == 0;
    }

public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        std::vector<std::string> result;
        if (s.empty()) return {""};

        std::queue<std::string> q;
        std::unordered_set<std::string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; ++i) {
                std::string curr = q.front();
                q.pop();

                if (isValid(curr)) {
                    result.push_back(curr);
                    found = true;
                }

                if (found) continue;

                for (int j = 0; j < curr.length(); ++j) {
                    if (curr[j] != '(' && curr[j] != ')') continue; 

                    std::string nextState = curr.substr(0, j) + curr.substr(j + 1);

                    if (!visited.count(nextState)) {
                        visited.insert(nextState);
                        q.push(nextState);
                    }
                }
            }

            if (found) break;
        }

        return result;
    }
};
