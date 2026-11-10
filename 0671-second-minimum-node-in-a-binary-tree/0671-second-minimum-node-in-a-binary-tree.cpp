/*
 * Approach: DFS. The root holds the global minimum, so look for the smallest
 * value strictly greater than it. A subtree whose root already exceeds the
 * minimum cannot contain anything smaller, so stop descending there.
 * Time: O(n), Space: O(h) recursion
 */
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        long long best = dfs(root, root->val);
        return best == LLONG_MAX ? -1 : (int)best;
    }

private:
    long long dfs(TreeNode* node, int minVal) {
        if (!node) return LLONG_MAX;
        if (node->val > minVal) return node->val;
        return min(dfs(node->left, minVal), dfs(node->right, minVal));
    }
};
