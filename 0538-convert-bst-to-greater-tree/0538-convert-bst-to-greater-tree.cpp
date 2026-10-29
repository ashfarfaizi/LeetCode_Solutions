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
    int sum = 0; // Tracks the cumulative sum of all greater keys visited so far

    void reverseInorder(TreeNode* node) {
        if (!node) return;

        // 1. Visit the right subtree first (greater values)
        reverseInorder(node->right);

        // 2. Process the current node
        sum += node->val;
        node->val = sum;

        // 3. Visit the left subtree (smaller values)
        reverseInorder(node->left);
    }

public:
    TreeNode* convertBST(TreeNode* root) {
        reverseInorder(root);
        return root;
    }
};