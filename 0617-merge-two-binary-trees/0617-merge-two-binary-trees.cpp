/*
 * Approach: Recurse on both trees together. If one side is missing, reuse the
 * other subtree as is; otherwise add the values into root1 and merge the
 * children recursively.
 * Time: O(min(m, n)), Space: O(min(h1, h2)) recursion
 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) return root2;
        if (!root2) return root1;
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};
