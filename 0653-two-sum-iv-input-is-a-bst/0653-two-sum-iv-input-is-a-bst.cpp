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
 * Approach: Inorder + two pointers. An inorder traversal of a BST yields a
 * sorted array; then move a left and right pointer inward until the pair
 * sums to k or the pointers meet.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> vals;
        inorder(root, vals);
        int lo = 0, hi = (int)vals.size() - 1;
        while (lo < hi) {
            int sum = vals[lo] + vals[hi];
            if (sum == k) return true;
            if (sum < k) ++lo;
            else --hi;
        }
        return false;
    }

private:
    void inorder(TreeNode* node, vector<int>& out) {
        if (!node) return;
        inorder(node->left, out);
        out.push_back(node->val);
        inorder(node->right, out);
    }
};
