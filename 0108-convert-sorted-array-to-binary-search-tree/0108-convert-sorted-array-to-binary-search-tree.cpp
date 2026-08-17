#include <vector>

using namespace std;

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
private:
    // Helper function to build the height-balanced BST recursively using a divide-and-conquer strategy
    TreeNode* sortedArrayToBSTHelper(const vector<int>& nums, int start, int end) {
        // Base case: if the segment boundaries cross, this subtree is empty
        if (start > end) {
            return nullptr;
        }

        // Always choose the middle element as the root node.
        // This ensures the number of nodes in the left and right subtrees 
        // differs by at most 1, keeping the tree height-balanced.
        int mid = start + (end - start) / 2;
        TreeNode* root = new TreeNode(nums[mid]);

        // Recursively build the left subtree from the left half of the current segment
        root->left = sortedArrayToBSTHelper(nums, start, mid - 1);

        // Recursively build the right subtree from the right half of the current segment
        root->right = sortedArrayToBSTHelper(nums, mid + 1, end);

        return root;
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // Kick off the recursion passing the entire bounds of the array
        return sortedArrayToBSTHelper(nums, 0, nums.size() - 1);
    }
};
