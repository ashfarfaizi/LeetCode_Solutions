class Solution {
public:
    string multiply(string num1, string num2) {
        // Step 1: Filter out structural zero instances instantly
        if (num1 == "0" || num2 == "0") return "0";
        
        int len1 = num1.length();
        int len2 = num2.length();
        
        // The maximum possible length of the product of two numbers is len1 + len2
        int max_digit_capacity = len1 + len2;
        vector<long long> digit_power_bins(max_digit_capacity, 0);
        
        // Step 2: Perform isolated convolution mapping
        // We accumulate raw cross-multiplication values without computing inline carries
        for (int i = 0; i < len1; ++i) {
            int digit1 = num1[i] - '0';
            for (int j = 0; j < len2; ++j) {
                int digit2 = num2[j] - '0';
                
                // Calculate position relative to the units column (right-to-left)
                int absolute_power_position = (len1 - 1 - i) + (len2 - 1 - j);
                
                digit_power_bins[absolute_power_position] += (digit1 * digit2);
            }
        }
        
        // Step 3: Single-pass carry normalization sweep
        long long current_carry = 0;
        string assembled_product = "";
        
        for (int i = 0; i < max_digit_capacity; ++i) {
            long long total_column_value = digit_power_bins[i] + current_carry;
            
            // Extract the unit digit for the current position
            int unit_digit = total_column_value % 10;
            current_carry = total_column_value / 10;
            
            assembled_product += to_string(unit_digit);
        }
        
        // Step 4: Format conversion and leading zero cleanup
        // Reverse string back to standard left-to-right reading configuration
        reverse(assembled_product.begin(), assembled_product.end());
        
        // Trim leading placeholder zeros left over from the max capacity estimation
        size_t first_valid_digit = assembled_product.find_first_not_of('0');
        if (first_valid_digit != string::npos) {
            return assembled_product.substr(first_valid_digit);
        }
        
        return "0";
    }
};

