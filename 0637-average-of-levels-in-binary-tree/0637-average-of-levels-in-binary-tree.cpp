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
 * Approach: Level-order BFS. Process the queue one level at a time, summing
 * values in a long long (node values can reach INT_MAX) and dividing by the
 * level size.
 * Time: O(n), Space: O(w) for the widest level
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> averages;
        if (!root) return averages;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int width = q.size();
            long long sum = 0;
            for (int i = 0; i < width; ++i) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            averages.push_back((double)sum / width);
        }
        return averages;
    }
};
