#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int findMinStep(string board, string hand) {
        // Sort the initial hand to handle identical hand combinations uniformly
        sort(hand.begin(), hand.end());
        unordered_map<string, int> mem;
        int ans = dfs(board, hand, mem);
        return ans == INT_MAX ? -1 : ans;
    }

private:
    int dfs(string board, string hand, unordered_map<string, int>& mem) {
        board = deDup(board);
        if (board.empty()) return 0;
        if (hand.empty()) return INT_MAX;

        string hashKey = board + '#' + hand;
        if (mem.find(hashKey) != mem.end()) {
            return mem[hashKey];
        }

        int ans = INT_MAX;

        // Try inserting every unique ball from the hand at every valid position
        for (int j = 0; j < hand.size(); ++j) {
            // Skip duplicate duplicate balls in hand to avoid identical branches
            if (j > 0 && hand[j] == hand[j - 1]) continue;

            for (int i = 0; i <= board.size(); ++i) {
                // Pruning rule 1: Only insert if it matches the current ball
                // or if it's inserted between two different balls that might need splitting
                if (i < board.size() && board[i] == hand[j]) {
                    // Good insertion spot
                } else if (i > 0 && i < board.size() && board[i - 1] == board[i] && board[i] != hand[j]) {
                    // Good insertion spot: splitting a pair with a different color
                } else {
                    continue; 
                }

                string newBoard = board.substr(0, i) + hand[j] + board.substr(i);
                string newHand = hand.substr(0, j) + hand.substr(j + 1);

                int res = dfs(newBoard, newHand, mem);
                if (res < INT_MAX) {
                    ans = min(ans, 1 + res);
                }
            }
        }

        return mem[hashKey] = ans;
    }

    // Recursively eliminates groups of 3 or more consecutive identical balls
    string deDup(string board) {
        int n = board.size();
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && board[j] == board[i]) {
                j++;
            }
            if (j - i >= 3) {
                return deDup(board.substr(0, i) + board.substr(j));
            }
            i = j;
        }
        return board;
    }
};
