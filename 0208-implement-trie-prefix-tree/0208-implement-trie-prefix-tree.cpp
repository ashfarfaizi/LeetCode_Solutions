#include <string>
#include <vector>

class TrieNode {
public:
    // Array to store links to child nodes (26 letters for 'a'-'z')
    TrieNode* children[26];
    // Flag to denote if a word ends at this node
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    // Initializes the trie object.
    Trie() {
        root = new TrieNode();
    }
    
    // Inserts the string word into the trie.
    void insert(std::string word) {
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
    
    // Returns true if the string word is in the trie, and false otherwise.
    bool search(std::string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }
    
    // Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
    bool startsWith(std::string prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        return true;
    }
};

