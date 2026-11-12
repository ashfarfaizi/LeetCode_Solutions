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
 * Approach: An in-order traversal of a BST visits values in sorted order, so
 * the minimum gap is between some pair of consecutive visited values.
 * Time: O(n), Space: O(h) for the recursion stack
 */
class Solution {
public:
    int minDiffInBST(TreeNode* root) {
        prev = nullptr;
        best = INT_MAX;
        inorder(root);
        return best;
    }

private:
    TreeNode* prev;
    int best;

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (prev) best = min(best, node->val - prev->val);
        prev = node;
        inorder(node->right);
    }
};
