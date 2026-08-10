#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int m, n;
    
    bool dfs(int r, int c, int index, vector<vector<char>>& board, const string& word) {
        // Base case: If we successfully matched all characters, return true
        if (index == word.length()) {
            return true;
        }

        // Boundary checks and character matching conditions
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != word[index]) {
            return false;
        }

        // Step 1: Save the original character and mark the cell as visited using a mask character
        char original_char = board[r][c];
        board[r][c] = '#'; 

        // Step 2: Explore all 4 adjacent directions (Up, Down, Left, Right)
        bool word_found = dfs(r + 1, c, index + 1, board, word) ||
                          dfs(r - 1, c, index + 1, board, word) ||
                          dfs(r, c + 1, index + 1, board, word) ||
                          dfs(r, c - 1, index + 1, board, word);

        // Step 3: Backtrack and restore the original character
        board[r][c] = original_char;

        return word_found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();

        // Pruning Optimization 1: Quick length verification
        if (word.length() > m * n) return false;

        // Pruning Optimization 2: Frequency map verification
        vector<int> board_freq(128, 0);
        vector<int> word_freq(128, 0);
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board_freq[board[i][j]]++;
            }
        }
        
        for (char c : word) {
            word_freq[c]++;
            if (word_freq[c] > board_freq[c]) {
                return false; // Board lacks enough copies of character c
            }
        }

        // Pruning Optimization 3: Reverse search if suffix matches are rarer than prefix matches
        if (board_freq[word[0]] > board_freq[word.back()]) {
            reverse(word.begin(), word.end());
        }

        // Run DFS traversal starting from every possible starting tile matching word[0]
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    if (dfs(i, j, 0, board, word)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};
