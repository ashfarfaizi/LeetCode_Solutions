class Solution {
public:
    int integerReplacement(int n) {
        long long num = n; // Use long long to handle potential overflow when num + 1
        int operations = 0;
        
        while (num > 1) {
            if ((num & 1) == 0) {
                // If even, divide by 2
                num >>= 1; 
            } else {
                // If odd, check the last two bits via modulo 4
                if (num == 3 || (num % 4 == 1)) {
                    num--;
                } else {
                    num++;
                }
            }
            operations++;
        }
        
        return operations;
    }
};
