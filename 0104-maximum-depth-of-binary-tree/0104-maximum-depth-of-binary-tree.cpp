#include <algorithm>

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
    int maxDepth(TreeNode* root) {
        // Base case: An empty tree has a depth of 0
        if (root == nullptr) {
            return 0;
        }
        
        // Recursively find the depth of the left subtree
        int leftDepth = maxDepth(root->left);
        
        // Recursively find the depth of the right subtree
        int rightDepth = maxDepth(root->right);
        
        // The maximum depth of the current node is the maximum of the two subtrees plus 1 (for the root node itself)
        return max(leftDepth, rightDepth) + 1;
    }
};
