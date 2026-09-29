class Solution {
public:
    int findNthDigit(int n) {
        long long len = 1;      // Number of digits (1-digit, 2-digit, etc.)
        long long count = 9;    // How many numbers exist in this digit group
        long long start = 1;    // The starting number of this group (1, 10, 100...)

        // Step 1: Find the length of the number that holds the nth digit
        while (n > len * count) {
            n -= len * count;
            len++;
            count *= 10;
            start *= 10;
        }

        // Step 2: Find the actual number where the nth digit is located
        // We subtract 1 because 'start' is already the 1st number of the group
        start += (n - 1) / len;

        // Step 3: Find the specific digit inside that target number
        string s = to_string(start);
        return s[(n - 1) % len] - '0';
    }
};
