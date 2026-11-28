/*
 * Approach: post-order DFS. A node becomes a new root if it survives and its
 * parent was deleted (or it is the original root). Deleted nodes return
 * nullptr so the parent unlinks them.
 * Time: O(n)   Space: O(n) for the hash set and recursion
 */
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> del(to_delete.begin(), to_delete.end());
        vector<TreeNode*> roots;
        dfs(root, true, del, roots);
        return roots;
    }

private:
    TreeNode* dfs(TreeNode* node, bool isRoot, const unordered_set<int>& del,
                  vector<TreeNode*>& roots) {
        if (!node) return nullptr;
        bool deleted = del.count(node->val) > 0;
        if (isRoot && !deleted) roots.push_back(node);
        node->left = dfs(node->left, deleted, del, roots);
        node->right = dfs(node->right, deleted, del, roots);
        return deleted ? nullptr : node;
    }
};
