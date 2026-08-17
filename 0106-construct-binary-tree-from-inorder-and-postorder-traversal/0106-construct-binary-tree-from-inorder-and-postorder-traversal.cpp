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
    TreeNode* buildTreeHelper(const vector<int>& postorder, int& postorderIdx, 
                             int inorderStart, int inorderEnd, 
                             unordered_map<int, int>& inorderMap) {
        // Base case: if the current boundary for inorder traversal is invalid
        if (inorderStart > inorderEnd) {
            return nullptr;
        }

        // The last element in the current postorder range is the root of this subtree
        int rootValue = postorder[postorderIdx];
        postorderIdx--; // Move the index backward as we process from root to leaves

        TreeNode* root = new TreeNode(rootValue);

        // Find the index of the root element in the inorder array to split into left and right subtrees
        int inorderRootIdx = inorderMap[rootValue];

        // CRITICAL STEP: Because postorder processes Left -> Right -> Root, 
        // traversing backward from the end yields Root -> Right -> Left.
        // Therefore, we must recursively build the right subtree before the left subtree.
        root->right = buildTreeHelper(postorder, postorderIdx, inorderRootIdx + 1, inorderEnd, inorderMap);

        // Recursively build the left subtree
        root->left = buildTreeHelper(postorder, postorderIdx, inorderStart, inorderRootIdx - 1, inorderMap);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // Hash map to store the value-to-index mapping of the inorder traversal array.
        // This allows us to locate the root's position in the inorder array in O(1) time.
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }

        // Start processing postorder from the very last element (the absolute root node)
        int postorderIdx = postorder.size() - 1;
        return buildTreeHelper(postorder, postorderIdx, 0, inorder.size() - 1, inorderMap);
    }
};
