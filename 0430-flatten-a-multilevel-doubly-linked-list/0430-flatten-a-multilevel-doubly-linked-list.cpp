/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) return nullptr;
        
        Node* curr = head;
        while (curr != nullptr) {
            // If the current node has a child sub-list
            if (curr->child != nullptr) {
                Node* nextNode = curr->next;
                Node* childNode = curr->child;
                
                // Find the tail of the child sub-list
                Node* childTail = childNode;
                while (childTail->next != nullptr) {
                    childTail = childTail->next;
                }
                
                // Connect curr to childNode
                curr->next = childNode;
                childNode->prev = curr;
                curr->child = nullptr; // Important: Clear the child pointer
                
                // Connect childTail to the old nextNode (if it exists)
                childTail->next = nextNode;
                if (nextNode != nullptr) {
                    nextNode->prev = childTail;
                }
            }
            // Move to the next node in the main list
            curr = curr->next;
        }
        
        return head;
    }
};
