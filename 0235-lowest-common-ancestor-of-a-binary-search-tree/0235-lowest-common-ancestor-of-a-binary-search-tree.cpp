/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            // If both target nodes are greater than the current node, move right
            if (p->val > curr->val && q->val > curr->val) {
                curr = curr->right;
            }
            // If both target nodes are less than the current node, move left
            else if (p->val < curr->val && q->val < curr->val) {
                curr = curr->left;
            }
            // We found the split point (or one of the nodes matches curr)
            else {
                return curr;
            }
        }
        
        return nullptr;
    }
};
