/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/*
 * Approach: DFS carrying the maximum value seen on the path from the root.
 * A node is good when its value is at least that maximum; update the maximum
 * before descending into its children.
 *
 * Time:  O(n)
 * Space: O(h) recursion depth
 */
class Solution {
public:
    int goodNodes(TreeNode* root) {
        return dfs(root, INT_MIN);
    }

private:
    int dfs(TreeNode* node, int pathMax) {
        if (!node) return 0;
        int good = node->val >= pathMax ? 1 : 0;
        int m = max(pathMax, node->val);
        return good + dfs(node->left, m) + dfs(node->right, m);
    }
};
