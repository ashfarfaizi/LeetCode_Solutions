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
 * Approach: Subtree IDs. Post-order traverse and map each subtree's
 * (left id, value, right id) triple to a small integer id. The first time an
 * id is seen a second time, the current node is a duplicate root.
 * Time: O(n log n) with the ordered map, Space: O(n)
 */
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> result;
        map<tuple<int, int, int>, int> ids;
        unordered_map<int, int> seen;
        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (!node) return 0;
            auto key = make_tuple(dfs(node->left), node->val, dfs(node->right));
            auto it = ids.find(key);
            int id = it != ids.end() ? it->second : (ids[key] = (int)ids.size() + 1);
            if (++seen[id] == 2) result.push_back(node);
            return id;
        };
        dfs(root);
        return result;
    }
};
