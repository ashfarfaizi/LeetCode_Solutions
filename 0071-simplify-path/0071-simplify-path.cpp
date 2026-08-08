#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        stringstream ss(path);
        string token;

        // Split the string into component tokens by slash delimiters
        while (getline(ss, token, '/')) {
            // Ignore empty tokens from consecutive slashes or single period indicators
            if (token == "" || token == ".") {
                continue;
            }
            
            // Pop the last directory from the stack if a double period instruction is hit
            if (token == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } 
            // All other non-empty strings are valid directory/file names
            else {
                stack.push_back(token);
            }
        }

        // Reconstruct the simplified canonical string from our stack structure
        string canonical_path = "";
        for (const string& dir : stack) {
            canonical_path += "/" + dir;
        }

        // If the path contains no elements, return the default root path
        return canonical_path.empty() ? "/" : canonical_path;
    }
};
