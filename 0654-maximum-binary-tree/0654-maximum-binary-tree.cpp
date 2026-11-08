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
 * Approach: Monotonic stack. Scan left to right keeping a stack of nodes with
 * decreasing values. Every node popped by a larger value becomes that value's
 * left child; the new node becomes the right child of whatever remains on top.
 * The bottom of the stack is the root.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for (int x : nums) {
            TreeNode* node = new TreeNode(x);
            while (!stk.empty() && stk.back()->val < x) {
                node->left = stk.back();
                stk.pop_back();
            }
            if (!stk.empty()) stk.back()->right = node;
            stk.push_back(node);
        }
        return stk.empty() ? nullptr : stk.front();
    }
};
