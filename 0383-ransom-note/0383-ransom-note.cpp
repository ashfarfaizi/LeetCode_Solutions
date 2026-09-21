class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // Fast I/O optimization
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        // Quick check: if ransomNote is longer than magazine, it's impossible
        if (ransomNote.length() > magazine.length()) {
            return false;
        }
        
        // Frequency array for 26 lowercase English letters
        int counts[26] = {0};
        
        // Count characters in magazine
        for (char c : magazine) {
            counts[c - 'a']++;
        }
        
        // Verify if ransomNote can be formed
        for (char c : ransomNote) {
            if (--counts[c - 'a'] < 0) {
                return false;
            }
        }
        
        return true;
    }
};
