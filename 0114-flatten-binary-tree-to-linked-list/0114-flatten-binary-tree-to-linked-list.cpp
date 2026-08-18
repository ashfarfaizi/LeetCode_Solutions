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
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            // If the current node has a left child, we need to restructure it
            if (curr->left != nullptr) {
                // Find the rightmost node in the left subtree (Preorder predecessor)
                TreeNode* predecessor = curr->left;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                
                // Connect the original right subtree to the right of the predecessor
                predecessor->right = curr->right;
                
                // Move the entire left subtree to become the right subtree
                curr->right = curr->left;
                curr->left = nullptr; // Explicitly set the left child to null
            }
            
            // Advance forward to the next node on the right path
            curr = curr->right;
        }
    }
};
