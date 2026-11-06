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
 * Approach: Post-order DFS returning each subtree's sum. A node's tilt is
 * |leftSum - rightSum|; accumulate it while the sums bubble up.
 * Time: O(n), Space: O(h) recursion
 */
class Solution {
public:
    int findTilt(TreeNode* root) {
        int total = 0;
        subtreeSum(root, total);
        return total;
    }

private:
    int subtreeSum(TreeNode* node, int& total) {
        if (!node) return 0;
        int l = subtreeSum(node->left, total);
        int r = subtreeSum(node->right, total);
        total += abs(l - r);
        return node->val + l + r;
    }
};
