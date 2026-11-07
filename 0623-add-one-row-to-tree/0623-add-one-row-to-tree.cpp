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
 * Approach: BFS down to depth - 1. For each node on that level, insert a new
 * left child that adopts the old left subtree (as its left) and a new right
 * child that adopts the old right subtree (as its right). Depth 1 is a
 * special case: the new node becomes the root with the old tree on its left.
 * Time: O(n), Space: O(w) for the widest level
 */
class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) return new TreeNode(val, root, nullptr);
        queue<TreeNode*> q;
        q.push(root);
        for (int level = 1; level < depth - 1; ++level) {
            for (int i = q.size(); i > 0; --i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            node->left = new TreeNode(val, node->left, nullptr);
            node->right = new TreeNode(val, nullptr, node->right);
        }
        return root;
    }
};
