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
/*
 * Approach: in-order traversal relinking nodes as we visit them. A dummy
 * head's tail pointer (passed by reference) receives each visited node as its right child, and the
 * node's left link is cleared.
 *
 * Time:  O(n)
 * Space: O(h) recursion depth
 */
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode dummy;
        TreeNode* tail = &dummy;
        inorder(root, tail);
        return dummy.right;
    }

private:
    static void inorder(TreeNode* node, TreeNode*& tail) {
        if (!node) return;
        inorder(node->left, tail);
        node->left = nullptr;
        tail->right = node;
        tail = node;
        inorder(node->right, tail);
    }
};
