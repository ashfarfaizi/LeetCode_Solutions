/*
 * Approach: Descend iteratively to the null slot where the value belongs
 * and attach a new leaf there. An empty tree becomes the new node.
 * Time: O(h), Space: O(1)
 */
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode* node = new TreeNode(val);
        if (!root) return node;
        TreeNode* cur = root;
        while (true) {
            TreeNode*& next = val < cur->val ? cur->left : cur->right;
            if (!next) {
                next = node;
                break;
            }
            cur = next;
        }
        return root;
    }
};
