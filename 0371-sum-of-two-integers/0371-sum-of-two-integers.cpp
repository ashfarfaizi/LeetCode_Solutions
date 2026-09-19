class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            // Find the carry bits
            int carry = a & b;
            
            // Sum of bits where at least one is 0
            a = a ^ b;
            
            // Shift the carry to add it in the next iteration
            // Cast to unsigned int to safely handle negative number left-shifts in C++
            b = (unsigned int)carry << 1;
        }
        return a;
    }
};
