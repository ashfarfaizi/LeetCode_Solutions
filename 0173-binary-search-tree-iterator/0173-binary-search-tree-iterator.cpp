#include <stack>

class BSTIterator {
private:
    // Stack to store ancestors of the current node
    std::stack<TreeNode*> node_stack;

    // Helper function to push all left children of a node onto the stack
    void pushAllLeft(TreeNode* node) {
        while (node != nullptr) {
            node_stack.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        // Initialize the stack with the path to the smallest node
        pushAllLeft(root);
    }
    
    int next() {
        // The top of the stack is always the next smallest element
        TreeNode* current_node = node_stack.top();
        node_stack.pop();
        
        // If the popped node has a right child, maintain in-order tracking 
        // by pushing all left descendants of that right child
        if (current_node->right != nullptr) {
            pushAllLeft(current_node->right);
        }
        
        return current_node->val;
    }
    
    bool hasNext() {
        // If the stack contains elements, a next node exists
        return !node_stack.empty();
    }
};
