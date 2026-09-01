#include <vector>
#include <string>

class TrieNode {
public:
    TrieNode* children[26];
    std::string word; // Stores the complete word at the leaf node, empty string otherwise

    TrieNode() {
        word = "";
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Solution {
private:
    TrieNode* buildTrie(const std::vector<std::string>& words) {
        TrieNode* root = new TrieNode();
        for (const std::string& w : words) {
            TrieNode* curr = root;
            for (char ch : w) {
                int idx = ch - 'a';
                if (curr->children[idx] == nullptr) {
                    curr->children[idx] = new TrieNode();
                }
                curr = curr->children[idx];
            }
            curr->word = w; // Save the word at the terminal node
        }
        return root;
    }

    void dfs(std::vector<std::vector<char>>& board, int r, int c, TrieNode* currNode, std::vector<std::string>& result) {
        char ch = board[r][c];
        int idx = ch - 'a';
        
        // Base Case: If character is not in Trie, abort this path
        if (currNode->children[idx] == nullptr) return;

        TrieNode* nextNode = currNode->children[idx];
        
        // If we matched a complete word, add it to result
        if (!nextNode->word.empty()) {
            result.push_back(nextNode->word);
            nextNode->word = ""; // Prevent matching the same word multiple times
        }

        // Mark cell as visited by overwriting it with a placeholder
        board[r][c] = '#';

        // Explore 4 directional neighbors
        int rowOffsets[] = {-1, 1, 0, 0};
        int colOffsets[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newRow = r + rowOffsets[i];
            int newCol = c + colOffsets[i];

            if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board[0].size() && board[newRow][newCol] != '#') {
                dfs(board, newRow, newCol, nextNode, result);
            }
        }

        // Backtrack: Restore the original character to the board cell
        board[r][c] = ch;

        // Optimization (Trie Pruning): Delete dead leaves to speed up remaining searches
        bool hasChildren = false;
        for (int i = 0; i < 26; ++i) {
            if (nextNode->children[i] != nullptr) {
                hasChildren = true;
                break;
            }
        }
        if (!hasChildren && nextNode->word.empty()) {
            delete nextNode;
            currNode->children[idx] = nullptr;
        }
    }

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        std::vector<std::string> result;
        if (board.empty() || board[0].empty() || words.empty()) return result;

        // Step 1: Parse words list into a consolidated prefix tree
        TrieNode* root = buildTrie(words);

        // Step 2: Iterate through every grid coordinate as a potential path starting position
        int rows = board.size();
        int cols = board[0].size();
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dfs(board, r, c, root, result);
            }
        }

        return result;
    }
};
