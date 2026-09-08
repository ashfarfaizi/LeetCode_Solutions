#include <string>
#include <sstream>
#include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    // Helper function to handle the recursive DFS serialization
    void buildString(TreeNode* root, std::string& res) {
        if (!root) {
            res += "#,";
            return;
        }
        res += std::to_string(root->val) + ",";
        buildString(root->left, res);
        buildString(root->right, res);
    }

    // Helper function to handle the recursive DFS deserialization
    TreeNode* buildTree(std::stringstream& ss) {
        std::string token;
        if (!std::getline(ss, token, ',')) {
            return nullptr;
        }

        if (token == "#") {
            return nullptr;
        }

        // Create the current root node
        TreeNode* root = new TreeNode(std::stoi(token));
        // Recursively construct left and right children from the remaining stream
        root->left = buildTree(ss);
        root->right = buildTree(ss);
        
        return root;
    }

public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string res = "";
        buildString(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        std::stringstream ss(data);
        return buildTree(ss);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
