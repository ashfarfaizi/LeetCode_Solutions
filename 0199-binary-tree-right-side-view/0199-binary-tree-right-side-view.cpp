class Solution {
public:
    void dfs(TreeNode* root, int level, vector<int>& res) {
        if (!root) return;
        
        // If this is the first time we visit this depth level, 
        // the node must be the rightmost visible node.
        if (level == res.size()) {
            res.push_back(root->val);
        }
        
        // Traverse the right branch first to ensure rightmost view visibility
        dfs(root->right, level + 1, res);
        dfs(root->left, level + 1, res);
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }
};
