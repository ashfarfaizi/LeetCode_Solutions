#include <algorithm>
#include <climits>

class Solution {
private:
    int minDiff = INT_MAX;
    TreeNode* prev = nullptr;

    void inorder(TreeNode* node) {
        if (!node) return;

        // 1. Traverse the left subtree
        inorder(node->left);

        // 2. Process the current node
        if (prev != nullptr) {
            minDiff = std::min(minDiff, node->val - prev->val);
        }
        prev = node; // Update the previous node pointer

        // 3. Traverse the right subtree
        inorder(node->right);
    }

public:
    int getMinimumDifference(TreeNode* root) {
        minDiff = INT_MAX;
        prev = nullptr;
        inorder(root);
        return minDiff;
    }
};
