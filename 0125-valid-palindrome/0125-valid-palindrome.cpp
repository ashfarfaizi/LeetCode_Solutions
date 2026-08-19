
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric characters from the left side
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            // Skip non-alphanumeric characters from the right side
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare the lowercase versions of the characters
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            // Step both pointers closer toward the center
            left++;
            right--;
        }
        
        return true;
    }
};
