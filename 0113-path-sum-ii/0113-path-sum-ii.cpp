#pragma GCC optimize ("O2")
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
    void findPaths(TreeNode* node, int remainingSum, vector<int>& currentPath, vector<vector<int>>& allPaths) {
        if (!node) {
            return;
        }

        // Add the current node's value to the tracking path
        currentPath.push_back(node->val);

        // Check if the current node is a leaf node and if it fulfills the target sum
        if (!node->left && !node->right && remainingSum == node->val) {
            allPaths.push_back(currentPath);
        } else {
            // Otherwise, continue traversing down the left and right subtrees
            findPaths(node->left, remainingSum - node->val, currentPath, allPaths);
            findPaths(node->right, remainingSum - node->val, currentPath, allPaths);
        }

        // Backtrack: Remove the current node from the path before returning to the parent call
        currentPath.pop_back();
    }

public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> allPaths;
        vector<int> currentPath;
        findPaths(root, targetSum, currentPath, allPaths);
        return allPaths;
    }
};
