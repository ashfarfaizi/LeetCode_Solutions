/*
 * Approach: Recursion using the BST property. A node below low can only keep
 * nodes from its right subtree, a node above high only from its left subtree;
 * otherwise keep the node and trim both children.
 * Time: O(n), Space: O(h) recursion
 */
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (!root) return nullptr;
        if (root->val < low) return trimBST(root->right, low, high);
        if (root->val > high) return trimBST(root->left, low, high);
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};
