class Solution {
public:
    int findComplement(int num) {
        unsigned int mask = 1;
        
        // Find a mask of 1s that matches the bit-length of num
        while (mask < num) {
            mask = (mask << 1) | 1;
        }
        
        // XOR the number with the mask to flip its bits
        return num ^ mask;
    }
};
