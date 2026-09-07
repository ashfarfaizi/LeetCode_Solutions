// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1;
        int high = n;
        int first_bad = n; // Keep track of the earliest bad version found
        
        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevents integer overflow
            
            if (isBadVersion(mid)) {
                first_bad = mid;  // This could be the first bad version
                high = mid - 1;   // Look left to find an even earlier bad version
            } else {
                low = mid + 1;    // If mid is good, the first bad version must be to the right
            }
        }
        
        return first_bad;
    }
};
