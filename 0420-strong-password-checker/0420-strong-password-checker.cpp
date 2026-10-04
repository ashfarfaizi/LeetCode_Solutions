#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.length();
        
        // 1. Check missing character types
        bool has_lower = false, has_upper = false, has_digit = false;
        for (char c : password) {
            if (islower(c)) has_lower = true;
            if (isupper(c)) has_upper = true;
            if (isdigit(c)) has_digit = true;
        }
        int missing_types = (has_lower ? 0 : 1) + (has_upper ? 0 : 1) + (has_digit ? 0 : 1);
        
        // 2. Collect repeating group lengths
        vector<int> groups;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && password[j] == password[i]) {
                j++;
            }
            int len = j - i;
            if (len >= 3) {
                groups.push_back(len);
            }
            i = j;
        }
        
        // Case 1: Too short
        if (n < 6) {
            return max(6 - n, missing_types);
        }
        
        // Count base replacements needed to fix repeating groups
        int replacements = 0;
        for (int len : groups) {
            replacements += len / 3;
        }
        
        // Case 2: Perfect length range
        if (n <= 20) {
            return max(replacements, missing_types);
        }
        
        // Case 3: Too long (n > 20)
        int deletions = n - 20;
        int over = deletions;
        
        // Step 3a: Eliminate groups of len % 3 == 0 using 1 deletion
        for (int &len : groups) {
            if (over > 0 && len % 3 == 0) {
                len -= 1;
                over -= 1;
            }
        }
        
        // Step 3b: Eliminate groups of len % 3 == 1 using 2 deletions
        for (int &len : groups) {
            if (over >= 2 && len % 3 == 1) {
                len -= 2;
                over -= 2;
            }
        }
        
        // Step 3c: Eliminate remaining groups using 3 deletions per replacement saved
        for (int &len : groups) {
            if (over > 0 && len >= 3) {
                int remove = min(over, len - 2);
                len -= remove;
                over -= remove;
            }
        }
        
        // Recalculate remaining replacements after optimized deletions
        replacements = 0;
        for (int len : groups) {
            replacements += len / 3;
        }
        
        return deletions + max(replacements, missing_types);
    }
};
