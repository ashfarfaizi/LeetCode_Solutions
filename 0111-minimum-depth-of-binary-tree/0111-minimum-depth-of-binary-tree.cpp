#pragma GCC optimize ("O2")
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
    int minDepth(TreeNode* root) {
        // Base case: An empty tree has a depth of 0
        if (!root) {
            return 0;
        }
        
        // Use a queue to implement a standard level-order BFS traversal
        // The queue stores pairs containing the current node pointer and its respective depth level
        queue<pair<TreeNode*, int>> q;
        q.push({root, 1});
        
        while (!q.empty()) {
            auto [curr, depth] = q.front();
            q.pop();
            
            // Critical Check: Because BFS processes the tree layer-by-layer, 
            // the very first leaf node encountered is guaranteed to be the closest one to the root.
            if (!curr->left && !curr->right) {
                return depth;
            }
            
            // If the left child exists, push it to the queue with incremented depth
            if (curr->left) {
                q.push({curr->left, depth + 1});
            }
            
            // If the right child exists, push it to the queue with incremented depth
            if (curr->right) {
                q.push({curr->right, depth + 1});
            }
        }
        
        return 0;
    }
};
