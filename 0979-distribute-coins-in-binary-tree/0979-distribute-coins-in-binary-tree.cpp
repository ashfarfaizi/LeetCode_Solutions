/*
 * Approach: post-order DFS returning each subtree's excess, i.e.
 * (coins in subtree) - (nodes in subtree). That excess must cross the edge
 * between the subtree and its parent, one move per coin in either
 * direction, so the answer is the sum of |excess| over every edge.
 *
 * Time:  O(n)
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
    int distributeCoins(TreeNode* root) {
        int moves = 0;
        excess(root, moves);
        return moves;
    }

private:
    int excess(TreeNode* node, int& moves) {
        if (!node) return 0;
        int left = excess(node->left, moves);
        int right = excess(node->right, moves);
        moves += abs(left) + abs(right);
        return node->val + left + right - 1;
    }
};
