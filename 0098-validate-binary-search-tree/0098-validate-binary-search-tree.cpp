#include <climits>

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
    bool isValidBST(TreeNode* root) {
        // Use long long boundaries to safely handle INT_MIN and INT_MAX node values
        return validate(root, LLONG_MIN, LLONG_MAX);
    }

private:
    // Helper function to validate if a subtree falls strictly within the permitted (min, max) range
    bool validate(TreeNode* node, long long minVal, long long maxVal) {
        // An empty tree/leaf child is inherently a valid BST
        if (node == nullptr) {
            return true;
        }

        // The current node value must be strictly greater than minVal and strictly less than maxVal
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }

        // Recursively validate left and right subtrees with updated bounds:
        // Left child value must be less than current node's value (maxVal becomes node->val)
        // Right child value must be greater than current node's value (minVal becomes node->val)
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    }
};
