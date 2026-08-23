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
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        stack<TreeNode*> nodeStack;
        nodeStack.push(root);

        // Traverse to get Root -> Right -> Left sequence
        while (!nodeStack.empty()) {
            TreeNode* curr = nodeStack.top();
            nodeStack.pop();

            result.push_back(curr->val);

            // Push left first so right is popped and processed next
            if (curr->left != nullptr) {
                nodeStack.push(curr->left);
            }
            if (curr->right != nullptr) {
                nodeStack.push(curr->right);
            }
        }

        // Reverse the vector to get Left -> Right -> Root sequence
        reverse(result.begin(), result.end());
        return result;
    }
};
