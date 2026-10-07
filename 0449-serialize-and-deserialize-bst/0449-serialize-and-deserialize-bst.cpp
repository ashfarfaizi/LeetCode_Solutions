class Codec {
private:
    // Helper function for Preorder traversal encoding
    void serializePreorder(TreeNode* root, string& s) {
        if (!root) return;
        
        // Convert the integer directly to its 4-byte raw memory representation
        int val = root->val;
        s.append(reinterpret_cast<const char*>(&val), sizeof(val));
        
        serializePreorder(root->left, s);
        serializePreorder(root->right, s);
    }

    // Helper function for building the BST using upper/lower range boundaries
    TreeNode* deserializePreorder(const string& data, int& pos, int lower, int upper) {
        if (pos >= data.size()) return nullptr;
        
        // Extract the 4-byte integer from the current position
        int val;
        memcpy(&val, &data[pos], sizeof(val));
        
        // If the value does not belong to the current BST subtree range, return null
        if (val < lower || val > upper) return nullptr;
        
        // Advance pointer since the value is valid for this node
        pos += sizeof(val);
        
        TreeNode* root = new TreeNode(val);
        root->left = deserializePreorder(data, pos, lower, val);
        root->right = deserializePreorder(data, pos, val, upper);
        
        return root;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string result = "";
        serializePreorder(root, result);
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return deserializePreorder(data, pos, INT_MIN, INT_MAX);
    }
};
