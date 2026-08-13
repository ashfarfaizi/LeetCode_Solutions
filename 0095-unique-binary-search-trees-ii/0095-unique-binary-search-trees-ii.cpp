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
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return buildTrees(1, n);
    }

private:
    // Helper function to generate all unique BSTs formed by values in range [start, end]
    vector<TreeNode*> buildTrees(int start, int end) {
        vector<TreeNode*> allTrees;
        
        // Base case: If start > end, no nodes can be formed, so return a vector containing nullptr
        if (start > end) {
            allTrees.push_back(nullptr);
            return allTrees;
        }
        
        // Iterate through each value i from start to end to treat it as the root
        for (int i = start; i <= end; ++i) {
            // Recursively generate all unique left subtrees using values less than i
            vector<TreeNode*> leftSubtrees = buildTrees(start, i - 1);
            
            // Recursively generate all unique right subtrees using values greater than i
            vector<TreeNode*> rightSubtrees = buildTrees(i + 1, end);
            
            // Connect the root i with every combination of left and right subtrees
            for (TreeNode* left : leftSubtrees) {
                for (TreeNode* right : rightSubtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    allTrees.push_back(root);
                }
            }
        }
        
        return allTrees;
    }
};
