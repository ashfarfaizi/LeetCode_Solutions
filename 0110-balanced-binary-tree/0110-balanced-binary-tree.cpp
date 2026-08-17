#include <algorithm>
#include <cmath>

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
private:
    // Helper function that returns the height of the subtree if it is balanced.
    // If any subtree is discovered to be unbalanced, it immediately returns -1.
    int calculateHeightAndCheckBalance(TreeNode* root) {
        // Base case: An empty tree is height-balanced and has a height of 0.
        if (root == nullptr) {
            return 0;
        }

        // Post-order traversal: Process the left subtree first
        int leftHeight = calculateHeightAndCheckBalance(root->left);
        if (leftHeight == -1) {
            return -1; // Propagate the unbalance signal upwards immediately
        }

        // Post-order traversal: Process the right subtree next
        int rightHeight = calculateHeightAndCheckBalance(root->right);
        if (rightHeight == -1) {
            return -1; // Propagate the unbalance signal upwards immediately
        }

        // Process the current root node: Check if current node breaks the balance property
        if (abs(leftHeight - rightHeight) > 1) {
            return -1; // Current node is unbalanced, return the error signal
        }

        // If balanced, return the actual height of the current subtree
        return max(leftHeight, rightHeight) + 1;
    }

public:
    bool isBalanced(TreeNode* root) {
        // The tree is balanced if our helper function does not return the failure signal (-1)
        return calculateHeightAndCheckBalance(root) != -1;
    }
};
