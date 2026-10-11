// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        while (true) {
            // Generate a uniform range from 1 to 49
            int row = rand7();
            int col = rand7();
            int index = (row - 1) * 7 + col;
            
            // Accept only if it falls in the uniform pool of 1 to 40
            if (index <= 40) {
                return (index - 1) % 10 + 1;
            }
            
            // Rejection happens here; the loop rolls over for a retry
        }
    }
};
