/*
 * Approach: For every node of root, check whether the tree hanging from it is
 * identical to subRoot with a simple recursive equality test.
 * Time: O(m*n) worst case, Space: O(h) recursion
 */
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) return !subRoot;
        return same(root, subRoot) || isSubtree(root->left, subRoot) ||
               isSubtree(root->right, subRoot);
    }

private:
    bool same(TreeNode* a, TreeNode* b) {
        if (!a || !b) return a == b;
        return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
    }
};
