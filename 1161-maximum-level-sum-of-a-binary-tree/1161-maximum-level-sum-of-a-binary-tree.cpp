/*
 * Approach: level-order BFS, summing each level and keeping the first level
 * that achieves a strictly larger sum than any before it.
 * Time: O(n), Space: O(w) where w is the maximum width of the tree
 */
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        long long best = LLONG_MIN;
        int bestLevel = 1;
        for (int level = 1; !q.empty(); ++level) {
            long long sum = 0;
            for (int i = q.size(); i > 0; --i) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            if (sum > best) {
                best = sum;
                bestLevel = level;
            }
        }
        return bestLevel;
    }
};
