/*
 * Approach: Post-order DFS. For each node return the length of the longest
 * downward same-value arm starting there. A child's arm extends through the
 * node only if the child has the same value. The best path through a node
 * joins its left and right arms.
 * Time: O(n), Space: O(h)
 */
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        best = 0;
        arm(root);
        return best;
    }

private:
    int best = 0;

    int arm(TreeNode* node) {
        if (!node) return 0;
        int l = arm(node->left), r = arm(node->right);
        int left = (node->left && node->left->val == node->val) ? l + 1 : 0;
        int right = (node->right && node->right->val == node->val) ? r + 1 : 0;
        best = max(best, left + right);
        return max(left, right);
    }
};
