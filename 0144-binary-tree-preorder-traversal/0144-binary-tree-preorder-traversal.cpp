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
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        stack<TreeNode*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            TreeNode* curr = nodeStack.top();
            nodeStack.pop();

            // Visit the root
            result.push_back(curr->val);

            // Push right child first so left child is processed first
            if (curr->right != nullptr) {
                nodeStack.push(curr->right);
            }
            if (curr->left != nullptr) {
                nodeStack.push(curr->left);
            }
        }

        return result;
    }
};
