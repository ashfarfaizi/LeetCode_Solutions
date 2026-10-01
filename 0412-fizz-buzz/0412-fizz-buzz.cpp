#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> fizzBuzz(int n) {
        std::vector<std::string> answer;
        // Optimize memory allocation upfront
        answer.reserve(n); 
        
        for (int i = 1; i <= n; ++i) {
            if (i % 3 == 0 && i % 5 == 0) {
                answer.push_back("FizzBuzz");
            } else if (i % 3 == 0) {
                answer.push_back("Fizz");
            } else if (i % 5 == 0) {
                answer.push_back("Buzz");
            } else {
                answer.push_back(std::to_string(i));
            }
        }
        
        return answer;
    }
};
