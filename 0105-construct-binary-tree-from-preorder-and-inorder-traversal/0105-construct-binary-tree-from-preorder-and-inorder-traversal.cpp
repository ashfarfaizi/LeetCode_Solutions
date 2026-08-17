#include <vector>
#include <unordered_map>

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
    // Helper function to recursively construct the binary tree
    TreeNode* buildTreeHelper(const vector<int>& preorder, int& preorderIdx, 
                             int inorderStart, int inorderEnd, 
                             unordered_map<int, int>& inorderMap) {
        // Base case: if the current boundary for inorder traversal is invalid
        if (inorderStart > inorderEnd) {
            return nullptr;
        }

        // The first element in the current preorder range is the root of this subtree
        int rootValue = preorder[preorderIdx];
        preorderIdx++; // Move the index forward for subsequent subtrees

        TreeNode* root = new TreeNode(rootValue);

        // Find the index of the root element in the inorder array to split into left and right subtrees
        int inorderRootIdx = inorderMap[rootValue];

        // Recursively build the left subtree using the elements to the left of the root in inorder
        root->left = buildTreeHelper(preorder, preorderIdx, inorderStart, inorderRootIdx - 1, inorderMap);

        // Recursively build the right subtree using the elements to the right of the root in inorder
        root->right = buildTreeHelper(preorder, preorderIdx, inorderRootIdx + 1, inorderEnd, inorderMap);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Hash map to store the value-to-index mapping of the inorder traversal array.
        // This allows us to find the root's position in the inorder array in O(1) time.
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }

        int preorderIdx = 0;
        return buildTreeHelper(preorder, preorderIdx, 0, inorder.size() - 1, inorderMap);
    }
};
