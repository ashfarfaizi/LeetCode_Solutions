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
private:
    int globalMaxSum;

    // Helper function that calculates the maximum single branch contribution
    int calculateBranchGain(TreeNode* node) {
        if (!node) {
            return 0;
        }

        // Recursively compute the maximum branch gain from the left and right subtrees.
        // If a subtree returns a negative sum, we choose 0 (ignoring that branch completely).
        int leftGain = max(0, calculateBranchGain(node->left));
        int rightGain = max(0, calculateBranchGain(node->right));

        // Price out the complete structural path sum that splits/peaks at the current node
        int currentPathSum = node->val + leftGain + rightGain;

        // Update our global tracker if the current complete path sum is the absolute highest seen
        globalMaxSum = max(globalMaxSum, currentPathSum);

        // For the parent call, we can only extend ONE branch upwards.
        // Return the node's value combined with the single most profitable child branch.
        return node->val + max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        globalMaxSum = INT_MIN; // Initialize with the lowest possible integer boundary
        calculateBranchGain(root);
        return globalMaxSum;
    }
};
