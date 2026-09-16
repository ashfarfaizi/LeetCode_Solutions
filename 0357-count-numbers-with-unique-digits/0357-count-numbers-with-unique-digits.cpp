class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        // Base case: 10^0 = 1, range is 0 <= x < 1, which only includes 0.
        if (n == 0) return 1;
        
        int totalCount = 10; // For n = 1, unique numbers are 0 through 9
        int uniqueDigitsForLength = 9; 
        int availableChoices = 9;
        
        // Compute configurations for numbers with length 2 up to n
        for (int i = 2; i <= n && availableChoices > 0; ++i) {
            uniqueDigitsForLength *= availableChoices;
            totalCount += uniqueDigitsForLength;
            availableChoices--;
        }
        
        return totalCount;
    }
};
