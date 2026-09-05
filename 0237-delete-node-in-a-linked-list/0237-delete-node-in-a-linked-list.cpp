/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        // Since it is guaranteed that the node is not the tail, 
        // node->next is always valid.
        ListNode* nextNode = node->next;
        
        // Copy the value of the next node into the current node
        node->val = nextNode->val;
        
        // Bypass the next node
        node->next = nextNode->next;
        
        // Delete the detached duplicate node from memory
        delete nextNode;
    }
};
