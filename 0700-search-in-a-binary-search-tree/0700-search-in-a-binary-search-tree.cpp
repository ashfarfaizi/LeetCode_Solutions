/*
 * Approach: Walk down from the root using the BST ordering: go left when
 * the target is smaller, right when larger, stop on a match or null.
 * Time: O(h), Space: O(1)
 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root && root->val != val) {
            root = val < root->val ? root->left : root->right;
        }
        return root;
    }
};
