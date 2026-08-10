/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // Base case: An empty list or a list with only one node has no duplicates
        if (!head) {
            return nullptr;
        }

        ListNode* current = head;

        // Traverse the list until the second to last node
        while (current && current->next) {
            if (current->val == current->next->val) {
                // Duplicate found: Save pointer to the node we are skipping
                ListNode* duplicateNode = current->next;
                
                // Link across the duplicate node
                current->next = current->next->next;
                
                // Free memory to prevent memory leaks
                delete duplicateNode;
            } else {
                // No duplicate: Move the tracker pointer forward
                current = current->next;
            }
        }

        return head;
    }
};
