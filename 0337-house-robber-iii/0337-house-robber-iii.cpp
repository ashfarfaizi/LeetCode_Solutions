#include <algorithm>
#include <utility>

using namespace std;

/* 
 * NOTE: The 'struct TreeNode' definition is automatically handled by LeetCode.
 * Do not uncomment or paste it in the code box.
 */

class Solution {
public:
    int rob(TreeNode* root) {
        pair<int, int> result = dfs(root);
        return max(result.first, result.second);
    }

private:
    // Returns a pair: {money_if_robbed, money_if_skipped}
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        
        // Post-order traversal (bottom-up DP)
        pair<int, int> leftChoices = dfs(node->left);
        pair<int, int> rightChoices = dfs(node->right);
        
        // 1. If we rob this current house, we cannot rob its immediate children
        int robCurrent = node->val + leftChoices.second + rightChoices.second;
        
        // 2. If we skip this house, we can choose the best strategy for its children
        int skipCurrent = max(leftChoices.first, leftChoices.second) + 
                          max(rightChoices.first, rightChoices.second);
        
        return {robCurrent, skipCurrent};
    }
};
