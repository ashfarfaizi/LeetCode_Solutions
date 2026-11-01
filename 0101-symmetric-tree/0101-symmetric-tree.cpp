/*
 * Approach: Recursively compare the left and right subtrees as mirror images:
 * outer children must match outer children and inner must match inner.
 * Time: O(n), Space: O(h) recursion stack
 */
class Solution {
    bool mirror(TreeNode* a, TreeNode* b) {
        if (!a || !b) return a == b;
        return a->val == b->val && mirror(a->left, b->right) && mirror(a->right, b->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return !root || mirror(root->left, root->right);
    }
};
