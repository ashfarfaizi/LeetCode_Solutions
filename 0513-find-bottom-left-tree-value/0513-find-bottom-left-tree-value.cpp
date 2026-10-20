
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        // Standard BFS queue holding the tree nodes
        queue<TreeNode*> q;
        q.push(root);
        
        TreeNode* current = nullptr;
        
        while (!q.empty()) {
            current = q.front();
            q.pop();
            
           
            if (current->right) {
                q.push(current->right);
            }
            if (current->left) {
                q.push(current->left);
            }
        }
        
        // The last node remaining after processing the whole tree
        return current->val;
    }
};
