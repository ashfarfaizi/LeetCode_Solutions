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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        // Flag to track the traversal direction (true = left to right, false = right to left)
        bool leftToRight = true;
        
        while (!q.empty()) {
            int levelSize = q.size();
            // Initialize vector with fixed size to allow direct index assignment
            vector<int> currentLevel(levelSize);
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* currentNode = q.front();
                q.pop();
                
                // Determine insertion position based on the current direction flag
                int index = leftToRight ? i : (levelSize - 1 - i);
                currentLevel[index] = currentNode->val;
                
                if (currentNode->left != nullptr) {
                    q.push(currentNode->left);
                }
                if (currentNode->right != nullptr) {
                    q.push(currentNode->right);
                }
            }
            
            result.push_back(currentLevel);
            // Invert the direction flag for the next level
            leftToRight = !leftToRight;
        }
        
        return result;
    }
};
