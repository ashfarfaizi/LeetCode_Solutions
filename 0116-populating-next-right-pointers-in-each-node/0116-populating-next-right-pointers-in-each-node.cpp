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
        
        // Start with the root node acting as the head of the current level
        Node* levelStart = root;
        
        // Loop down the levels as long as a child level exists
        while (levelStart->left != nullptr) {
            Node* curr = levelStart;
            
            // Traverse the current level horizontally using next pointers
            while (curr != nullptr) {
                // Connection Type 1: Link children belonging to the same parent node
                curr->left->next = curr->right;
                
                // Connection Type 2: Link children across different parent boundaries
                if (curr->next != nullptr) {
                    curr->right->next = curr->next->left;
                }
                
                // Move rightward within the active row level
                curr = curr->next;
            }
            
            // Step downward to the head node of the next layer row level
            levelStart = levelStart->left;
        }
        
        return root;
    }
};
