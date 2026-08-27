#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        // Convert all integers to strings
        std::vector<std::string> str_nums;
        for (int num : nums) {
            str_nums.push_back(std::to_string(num));
        }
        
        // Sort using custom comparator: if A + B > B + A, A should come before B
        std::sort(str_nums.begin(), str_nums.end(), [](const std::string& a, const std::string& b) {
            return a + b > b + a;
        });
        
        // Edge Case: If the largest number after sorting is "0", the entire result is "0"
        // (e.g., input was, we want to return "0", not "000")
        if (str_nums[0] == "0") {
            return "0";
        }
        
        // Concatenate sorted strings to form the final result
        std::string result = "";
        for (const std::string& str : str_nums) {
            result += str;
        }
        
        return result;
    }
};
