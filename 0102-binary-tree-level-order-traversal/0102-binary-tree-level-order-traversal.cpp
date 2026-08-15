#include <vector>
#include <queue>

using namespace std;

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            // Number of nodes present at the current level
            int levelSize = q.size();
            vector<int> currentLevel;
            
            // Process all nodes belonging to the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* currentNode = q.front();
                q.pop();
                
                currentLevel.push_back(currentNode->val);
                
                // Enqueue the left child if it exists
                if (currentNode->left != nullptr) {
                    q.push(currentNode->left);
                }
                // Enqueue the right child if it exists
                if (currentNode->right != nullptr) {
                    q.push(currentNode->right);
                }
            }
            
            // Add the level values to the final tracking array
            result.push_back(currentLevel);
        }
        
        return result;
    }
};
