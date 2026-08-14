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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case: If both nodes are null, the subtrees are identical
        if (p == nullptr && q == nullptr) {
            return true;
        }
        
        // If one node is null and the other is not, they are structurally different
        if (p == nullptr || q == nullptr) {
            return false;
        }
        
        // The current values must match, and both their left and right subtrees must be identical
        return (p->val == q->val) && 
               isSameTree(p->left, q->left) && 
               isSameTree(p->right, q->right);
    }
};
