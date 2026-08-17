#include <vector>
#include <queue>
#include <algorithm>

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        // Base case: if the tree is empty, return an empty vector
        if (!root) {
            return result;
        }

        // Queue to manage the Breadth-First Search (BFS) nodes
        queue<TreeNode*> q;
        q.push(root);

        // Standard level-order traversal (Top-to-Bottom)
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;

            // Process all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();

                currentLevel.push_back(node->val);

                // Enqueue the left child if it exists
                if (node->left) {
                    q.push(node->left);
                }
                // Enqueue the right child if it exists
                if (node->right) {
                    q.push(node->right);
                }
            }
            // Add the populated level data to our results vector
            result.push_back(currentLevel);
        }

        // Reverse the final 2D array to satisfy the Bottom-Up order requirement
        reverse(result.begin(), result.end());
        return result;
    }
}; // <- This closing brace and semicolon must close the class definition successfully
