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
    int calculateSum(TreeNode* node, int currentNumber) {
        // Base Case: If the current node is null, it contributes 0 to the sum
        if (node == nullptr) {
            return 0;
        }

        // Left shift the previous digits by multiplying by 10 and add the current node value
        currentNumber = currentNumber * 10 + node->val;

        // If a leaf node is reached, return the completed path number
        if (node->left == nullptr && node->right == nullptr) {
            return currentNumber;
        }

        // Recursively find the sum of paths in left and right subtrees
        int leftSum = calculateSum(node->left, currentNumber);
        int rightSum = calculateSum(node->right, currentNumber);

        return leftSum + rightSum;
    }

public:
    int sumNumbers(TreeNode* root) {
        return calculateSum(root, 0);
    }
};
