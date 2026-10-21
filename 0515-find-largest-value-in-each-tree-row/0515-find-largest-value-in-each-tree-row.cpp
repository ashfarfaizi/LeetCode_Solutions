class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            int max_val = INT_MIN;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                max_val = max(max_val, node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(max_val);
        }
        return result;
    }
};
