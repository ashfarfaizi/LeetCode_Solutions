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
 * Approach: collect each tree's leaves left to right with a DFS and compare
 * the two sequences.
 *
 * Time:  O(n1 + n2)
 * Space: O(h1 + h2) recursion plus O(leaves) for the sequences
 */
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> a, b;
        leaves(root1, a);
        leaves(root2, b);
        return a == b;
    }

private:
    void leaves(TreeNode* node, vector<int>& out) {
        if (!node) return;
        if (!node->left && !node->right) {
            out.push_back(node->val);
            return;
        }
        leaves(node->left, out);
        leaves(node->right, out);
    }
};
