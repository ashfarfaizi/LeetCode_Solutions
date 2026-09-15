class Solution {
public:
    // Helper function to check if a character is a vowel
    bool isVowel(char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    string reverseVowels(string s) {
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Move left pointer forward if it's not a vowel
            while (left < right && !isVowel(s[left])) {
                left++;
            }
            // Move right pointer backward if it's not a vowel
            while (left < right && !isVowel(s[right])) {
                right--;
            }
            
            // Swap the vowels and move pointers inward
            if (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
};
