class Solution {
private:
    // Helper function to find the minimum value node in a BST subtree
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        
        // Step 1: Navigate to the target node
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Step 2: Target node found! Handle deletion cases
            
            // Case 1 & 2: No left child or no children at all
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root; // Clean up memory
                return temp;
            }
            // Case 2: No right child
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root; // Clean up memory
                return temp;
            }
            
            // Case 3: Node has two children
            // Find the inorder successor (smallest in the right subtree)
            TreeNode* temp = findMin(root->right);
            
            // Replace root's value with successor's value
            root->val = temp->val;
            
            // Delete the duplicate inorder successor from the right subtree
            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }
};
