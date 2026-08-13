#include <vector>

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // dp[i] stores the number of structurally unique BSTs that can be formed with i nodes
        vector<int> dp(n + 1, 0);
        
        // Base cases: 
        // An empty tree (0 nodes) has 1 unique structure (empty).
        // A tree with 1 node has exactly 1 unique structure.
        dp[0] = 1;
        dp[1] = 1;
        
        // Fill the DP table iteratively for all node counts from 2 up to n
        for (int nodes = 2; nodes <= n; ++nodes) {
            // Consider each root position 'root' from 1 to 'nodes'
            for (int root = 1; root <= nodes; ++root) {
                int leftNodes = root - 1;
                int rightNodes = nodes - root;
                
                // The total combinations for a fixed root is the product of 
                // the unique left subtrees and unique right subtrees
                dp[nodes] += dp[leftNodes] * dp[rightNodes];
            }
        }
        
        return dp[n];
    }
};
