#include <string>
#include <vector>

class Solution {
private:
    const std::vector<std::string> LESS_THAN_20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    
    const std::vector<std::string> TENS = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };
    
    const std::vector<std::string> THOUSANDS = {"", "Thousand", "Million", "Billion"};

    // Helper function to process groups of three digits (< 1000)
    std::string helper(int num) {
        if (num == 0) return "";
        else if (num < 20) return LESS_THAN_20[num] + " ";
        else if (num < 100) return TENS[num / 10] + " " + helper(num % 10);
        else return LESS_THAN_20[num / 100] + " Hundred " + helper(num % 100);
    }

public:
    std::string numberToWords(int num) {
        if (num == 0) return "Zero";

        std::string words = "";
        int i = 0;

        while (num > 0) {
            if (num % 1000 != 0) {
                words = helper(num % 1000) + THOUSANDS[i] + " " + words;
            }
            num /= 1000;
            i++;
        }

        // Clean up trailing whitespaces caused by string concatenations
        while (!words.empty() && words.back() == ' ') {
            words.pop_back();
        }
        
        return words;
    }
};
