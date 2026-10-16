#include <vector>

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
    TreeNode* prev = nullptr;
    int currentCount = 0;
    int maxCount = 0;
    std::vector<int> modes;

    void inorder(TreeNode* node) {
        if (!node) return;

        // Traverse the left subtree
        inorder(node->left);

        // Process the current node
        if (prev != nullptr && node->val == prev->val) {
            currentCount++;
        } else {
            currentCount = 1;
        }

        // Check if we found a new mode or an equal maximum
        if (currentCount > maxCount) {
            maxCount = currentCount;
            modes.clear(); // Found a higher frequency, clear previous results
            modes.push_back(node->val);
        } else if (currentCount == maxCount) {
            modes.push_back(node->val); // Ties the max frequency, add to modes
        }

        // Move the tracking pointer forward
        prev = node;

        // Traverse the right subtree
        inorder(node->right);
    }

public:
    std::vector<int> findMode(TreeNode* root) {
        // Reset state variables for fresh execution
        prev = nullptr;
        currentCount = 0;
        maxCount = 0;
        modes.clear();
        
        inorder(root);
        return modes;
    }
};
