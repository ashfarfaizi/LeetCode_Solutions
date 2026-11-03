/*
 * Approach: Post-order DFS returning each subtree's height. At every node the
 * longest path through it is leftHeight + rightHeight edges; keep the max.
 * Time: O(n), Space: O(h) recursion
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int best = 0;
        height(root, best);
        return best;
    }

private:
    int height(TreeNode* node, int& best) {
        if (!node) return 0;
        int l = height(node->left, best);
        int r = height(node->right, best);
        best = max(best, l + r);
        return 1 + max(l, r);
    }
};
