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
    void dfs(TreeNode* node, string currentPath, vector<string>& allPaths) {
        if (!node) return;

        // Append the current node's value to the tracking path string
        if (!currentPath.empty()) {
            currentPath += "->";
        }
        currentPath += to_string(node->val);

        // Base case: If it's a leaf node, save the completed path string
        if (!node->left && !node->right) {
            allPaths.push_back(currentPath);
            return;
        }

        // Recursively search left and right subtrees
        if (node->left) dfs(node->left, currentPath, allPaths);
        if (node->right) dfs(node->right, currentPath, allPaths);
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> allPaths;
        if (!root) return allPaths;
        
        dfs(root, "", allPaths);
        return allPaths;
    }
};
