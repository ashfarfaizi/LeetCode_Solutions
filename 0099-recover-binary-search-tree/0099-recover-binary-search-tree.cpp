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
    void recoverTree(TreeNode* root) {
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        TreeNode* pred = nullptr; // Tracks the previously visited node in-order
        
        TreeNode* curr = root;
        
        // Morris Inorder Traversal to achieve O(1) auxiliary space
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                // Process the current node
                if (pred != nullptr && pred->val > curr->val) {
                    if (first == nullptr) {
                        first = pred;
                    }
                    second = curr;
                }
                pred = curr;
                curr = curr->right;
            } else {
                // Find the in-order predecessor of curr
                TreeNode* predecessor = curr->left;
                while (predecessor->right != nullptr && predecessor->right != curr) {
                    predecessor = predecessor->right;
                }
                
                if (predecessor->right == nullptr) {
                    // Create a temporary link (thread) back to the root parent
                    predecessor->right = curr;
                    curr = curr->left;
                } else {
                    // Thread already exists, break it to restore original tree structure
                    predecessor->right = nullptr;
                    
                    // Process the current node
                    if (pred != nullptr && pred->val > curr->val) {
                        if (first == nullptr) {
                            first = pred;
                    }
                        second = curr;
                    }
                    pred = curr;
                    curr = curr->right;
                }
            }
        }
        
        // Swap the values of the two misplaced nodes to recover the BST layout
        if (first != nullptr && second != nullptr) {
            std::swap(first->val, second->val);
        }
    }
};
