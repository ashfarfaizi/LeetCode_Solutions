#include <unordered_map>

using namespace std;

class Solution {
private:
    int totalPaths = 0;
    unordered_map<long long, int> prefixSumMap;

    void dfs(TreeNode* node, long long currentSum, int targetSum) {
        if (!node) return;

        // Update the running prefix sum
        currentSum += node->val;

        // Check if there is a prefix path we can subtract to get targetSum
        if (prefixSumMap.find(currentSum - targetSum) != prefixSumMap.end()) {
            totalPaths += prefixSumMap[currentSum - targetSum];
        }

        // Add the current prefix sum to the map
        prefixSumMap[currentSum]++;

        // Recurse into subtrees
        dfs(node->left, currentSum, targetSum);
        dfs(node->right, currentSum, targetSum);

        // Backtrack: Remove the current prefix sum before moving up
        prefixSumMap[currentSum]--;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        totalPaths = 0;
        prefixSumMap.clear();
        
        // Base case: An empty prefix path sums to 0
        prefixSumMap[0] = 1;
        
        dfs(root, 0, targetSum);
        return totalPaths;
    }
};
