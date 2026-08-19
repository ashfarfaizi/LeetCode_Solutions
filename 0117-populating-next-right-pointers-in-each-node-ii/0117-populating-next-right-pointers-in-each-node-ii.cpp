#pragma GCC optimize ("O2")
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        Node* currLevelHead = root; // Head node of the level currently being traversed
        
        // Loop runs as long as there is at least one node on the current level
        while (currLevelHead != nullptr) {
            Node* dummy = new Node(0); // Temporary dummy node to reference the next level's head
            Node* prevChild = dummy;   // Tracks the last processed child node on the next level
            Node* curr = currLevelHead; // Pointer to traverse the current level horizontally
            
            while (curr != nullptr) {
                // If a left child exists, link it to the next level chain
                if (curr->left != nullptr) {
                    prevChild->next = curr->left;
                    prevChild = prevChild->next;
                }
                // If a right child exists, link it to the next level chain
                if (curr->right != nullptr) {
                    prevChild->next = curr->right;
                    prevChild = prevChild->next;
                }
                // Move sideways to the next node on the current level
                curr = curr->next;
            }
            
            // Advance down to the next level's true head node
            currLevelHead = dummy->next;
            delete dummy; // Clean up the heap-allocated memory
        }
        
        return root;
    }
};
