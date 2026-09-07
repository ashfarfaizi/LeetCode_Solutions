#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    bool wordPattern(std::string pattern, std::string s) {
        // Tokenize the string s into a vector of words
        std::stringstream ss(s);
        std::string word;
        std::vector<std::string> words;
        
        while (ss >> word) {
            words.push_back(word);
        }
        
        // If the number of keys doesn't match the number of values, a bijection is impossible
        if (pattern.length() != words.size()) {
            return false;
        }
        
        std::unordered_map<char, std::string> charToWord;
        std::unordered_set<std::string> usedWords; // Keeps track of words already mapped
        
        for (int i = 0; i < pattern.length(); ++i) {
            char ch = pattern[i];
            std::string currWord = words[i];
            
            // If the character has been seen before
            if (charToWord.count(ch)) {
                // It must map to the exact same word
                if (charToWord[ch] != currWord) {
                    return false;
                }
            } else {
                // If the character is new, the word must also be unmapped
                if (usedWords.count(currWord)) {
                    return false; // Word already claimed by a different character
                }
                
                // Establish the new mapping
                charToWord[ch] = currWord;
                usedWords.insert(currWord);
            }
        }
        
        return true;
    }
};
