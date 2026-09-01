#include <string>
#include <vector>

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class WordDictionary {
private:
    TrieNode* root;

    // Helper function for recursive DFS search
    bool searchInNode(const std::string& word, int index, TrieNode* node) {
        if (node == nullptr) return false;
        
        // If we reached the end of the word, check if it forms a valid completed word
        if (index == word.length()) {
            return node->isEndOfWord;
        }

        char ch = word[index];

        if (ch == '.') {
            // Wildcard search: try all possible valid existing children branches
            for (int i = 0; i < 26; ++i) {
                if (node->children[i] != nullptr) {
                    if (searchInNode(word, index + 1, node->children[i])) {
                        return true;
                    }
                }
            }
            return false; // No branches matched the rest of the string
        } else {
            // Regular search: match the exact character branch
            int childIndex = ch - 'a';
            return searchInNode(word, index + 1, node->children[childIndex]);
        }
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(std::string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }
    
    bool search(std::string word) {
        return searchInNode(word, 0, root);
    }
};

