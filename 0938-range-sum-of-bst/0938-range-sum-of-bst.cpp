/*
 * Approach: DFS that uses the BST ordering to prune. If a node is below low,
 * only its right subtree can contribute; if it is above high, only its left
 * subtree can. Otherwise count the node and recurse both ways.
 *
 * Time:  O(n) worst case, fewer nodes visited when the range is narrow
 * Space: O(h) recursion depth
 */
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
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (!root) return 0;
        if (root->val < low) return rangeSumBST(root->right, low, high);
        if (root->val > high) return rangeSumBST(root->left, low, high);
        return root->val + rangeSumBST(root->left, low, high) +
               rangeSumBST(root->right, low, high);
    }
};
