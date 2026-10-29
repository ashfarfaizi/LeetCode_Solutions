#include <string>
#include <cstdio>

class Solution {
public:
    std::string complexNumberMultiply(std::string num1, std::string num2) {
        int a, b; // Real and imaginary parts of num1
        int c, d; // Real and imaginary parts of num2
        
        // Parse the integers out of the "real+imaginaryi" formatted string
        sscanf(num1.c_str(), "%d+%di", &a, &b);
        sscanf(num2.c_str(), "%d+%di", &c, &d);
        
        // Compute the resulting parts using the multiplication formula
        int real_part = a * c - b * d;
        int imag_part = a * d + b * c;
        
        // Format and return the result as a string
        return std::to_string(real_part) + "+" + std::to_string(imag_part) + "i";
    }
};
