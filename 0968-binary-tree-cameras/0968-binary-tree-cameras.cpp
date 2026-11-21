/*
 * Approach: greedy post-order DFS. Each node reports one of three states to
 * its parent: NOT_COVERED, HAS_CAMERA, or COVERED (watched but no camera).
 * A null child counts as COVERED so leaves never get cameras. If any child is
 * NOT_COVERED the node must hold a camera; else if any child has a camera the
 * node is covered; otherwise it is left uncovered for its parent to handle.
 * Placing cameras as high as possible like this is optimal. Finally, add a
 * camera at the root if it is still uncovered.
 *
 * Time:  O(n)
 * Space: O(h) recursion depth
 */
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
    enum State { NOT_COVERED, HAS_CAMERA, COVERED };
    int cameras = 0;

    State dfs(TreeNode* node) {
        if (!node) return COVERED;
        State l = dfs(node->left), r = dfs(node->right);
        if (l == NOT_COVERED || r == NOT_COVERED) {
            ++cameras;
            return HAS_CAMERA;
        }
        if (l == HAS_CAMERA || r == HAS_CAMERA) return COVERED;
        return NOT_COVERED;
    }

public:
    int minCameraCover(TreeNode* root) {
        cameras = 0;
        if (dfs(root) == NOT_COVERED) ++cameras;
        return cameras;
    }
};
