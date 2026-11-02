/*
 * Approach: Post-order recursion. A subtree returns p or q if it contains one
 * of them; the first node where both left and right return non-null is the
 * LCA. If only one side is non-null, propagate it upward.
 * Time: O(n), Space: O(h) recursion
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right) return root;
        return left ? left : right;
    }
};
