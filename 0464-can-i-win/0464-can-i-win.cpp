#include <vector>
#include <numeric>

class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        // Quick check 1: If target is 0 or less, the first player wins instantly.
        if (desiredTotal <= 0) return true;

        // Quick check 2: If the sum of all available numbers is less than the target,
        // no player can ever reach the total.
        int totalSum = (maxChoosableInteger * (maxChoosableInteger + 1)) / 2;
        if (totalSum < desiredTotal) return false;

        // Since maxChoosableInteger <= 20, there are 2^20 possible states.
        // We use a vector initialized to 0 (unvisited). 
        // 1 means the state leads to a win, 2 means it leads to a loss.
        std::vector<char> memo(1 << (maxChoosableInteger + 1), 0);
        
        return dfs(maxChoosableInteger, desiredTotal, 0, memo);
    }

private:
    bool dfs(int maxChoosable, int desiredTotal, int mask, std::vector<char>& memo) {
        // If we have already evaluated this game state, return the cached result
        if (memo[mask] != 0) return memo[mask] == 1;

        // Try picking every available integer
        for (int i = 1; i <= maxChoosable; ++i) {
            int currentBit = 1 << i;
            
            // If the number 'i' has not been chosen yet
            if ((mask & currentBit) == 0) {
                // If picking 'i' immediately hits or exceeds the target, we win
                if (i >= desiredTotal) {
                    memo[mask] = 1;
                    return true;
                }
                
                // If the next player CANNOT win after we pick 'i', then we win
                if (!dfs(maxChoosable, desiredTotal - i, mask | currentBit, memo)) {
                    memo[mask] = 1;
                    return true;
                }
            }
        }

        // If no choice guarantees a victory, this state is a loss
        memo[mask] = 2;
        return false;
    }
};
