#include <vector>
#include <stack>

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
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> nodeStack;
        TreeNode* current = root;
        
        // Loop runs until both the current pointer is null and the stack is empty
        while (current != nullptr || !nodeStack.empty()) {
            // Traverse to the leftmost node of the current subtree
            while (current != nullptr) {
                nodeStack.push(current);
                current = current->left;
            }
            
            // Current must be nullptr at this point, pop the top element from the stack
            current = nodeStack.top();
            nodeStack.pop();
            
            // Add the node value to our result vector (Inorder: Left -> Root -> Right)
            result.push_back(current->val);
            
            // Visit the right subtree
            current = current->right;
        }
        
        return result;
    }
};
