class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string longest_word = "";
        
        for (const string& word : dictionary) {
            // Optimization: Skip checking if the current word cannot beat our best result
            if (word.length() < longest_word.length() || 
               (word.length() == longest_word.length() && word >= longest_word)) {
                continue;
            }
            
            // Two-pointer check to see if 'word' is a subsequence of 's'
            int i = 0, j = 0;
            while (i < s.length() && j < word.length()) {
                if (s[i] == word[j]) {
                    j++;
                }
                i++;
            }
            
            // If the entire word matches as a subsequence, update our result
            if (j == word.length()) {
                longest_word = word;
            }
        }
        
        return longest_word;
    }
};
