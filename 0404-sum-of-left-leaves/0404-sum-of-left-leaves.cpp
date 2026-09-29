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
class Solution {
private:
    int dfs(TreeNode* root, bool isLeft) {
        if (!root) return 0;
        
        // Check if the current node is a leaf node
        if (!root->left && !root->right) {
            return isLeft ? root->val : 0;
        }
        
        // Sum values from both left and right subtrees
        return dfs(root->left, true) + dfs(root->right, false);
    }

public:
    int sumOfLeftLeaves(TreeNode* root) {
        // Start traversal from the root node; the root itself is not a left child
        return dfs(root, false);
    }
};
