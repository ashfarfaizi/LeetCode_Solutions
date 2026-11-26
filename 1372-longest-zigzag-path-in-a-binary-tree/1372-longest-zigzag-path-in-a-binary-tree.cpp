/*
 * Approach: DFS carrying two lengths into each node: the zigzag length if we
 * arrived here by going left, and if we arrived by going right. Going left
 * from a node continues a path that last went right, and vice versa; going
 * the same way twice restarts the count at 1.
 * Time: O(n), Space: O(h) recursion depth
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 * };
 */
class Solution {
    int best = 0;
    void dfs(TreeNode* node, int fromLeft, int fromRight) {
        if (!node) return;
        best = max({best, fromLeft, fromRight});
        dfs(node->left, fromRight + 1, 0);
        dfs(node->right, 0, fromLeft + 1);
    }
public:
    int longestZigZag(TreeNode* root) {
        best = 0;
        dfs(root, 0, 0);
        return best;
    }
};
