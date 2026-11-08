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
 * Approach: BFS with heap-style indices. Give the root index 0 and children
 * 2i+1 and 2i+2. Re-base each level's indices on its first node so they stay
 * small, and the width of a level is last - first + 1.
 * Time: O(n), Space: O(w) for the widest level
 */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        unsigned long long best = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});
        while (!q.empty()) {
            int size = q.size();
            unsigned long long first = q.front().second, last = first;
            for (int i = 0; i < size; ++i) {
                auto [node, idx] = q.front();
                q.pop();
                idx -= first;
                last = idx;
                if (node->left) q.push({node->left, 2 * idx + 1});
                if (node->right) q.push({node->right, 2 * idx + 2});
            }
            best = max(best, last + 1);
        }
        return (int)best;
    }
};
