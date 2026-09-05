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
    int kthSmallest(TreeNode* root, int k) {
        std::stack<TreeNode*> st;
        TreeNode* curr = root;
        
        while (curr != nullptr || !st.empty()) {
            // Go to the leftmost node of the current subtree
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            
            // Process the current top node
            curr = st.top();
            st.pop();
            
            k--;
            if (k == 0) {
                return curr->val; // Found the kth smallest element
            }
            
            // Move to the right subtree
            curr = curr->right;
        }
        
        return -1; // Fallback for invalid constraints
    }
};
