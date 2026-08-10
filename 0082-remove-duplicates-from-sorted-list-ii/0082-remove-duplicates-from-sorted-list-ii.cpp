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
        // Base case: An empty list or a single node cannot contain duplicates
        if (!head || !head->next) {
            return head;
        }

        // Dummy node initialization to cleanly handle edge cases at the head
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;

        while (head) {
            // Check if the current node is the start of a duplicate sequence
            if (head->next && head->val == head->next->val) {
                // Move the runner pointer to the end node of the duplicate run
                while (head->next && head->val == head->next->val) {
                    head = head->next;
                }
                // Bypass the entire duplicate sequence group
                prev->next = head->next;
            } else {
                // No duplicate found, advance the safe-zone pointer forward
                prev = prev->next;
            }
            // Advance runner head pointer
            head = head->next;
        }

        ListNode* uniqueHead = dummy->next;
        delete dummy; // Clean up the auxiliary memory allocation
        return uniqueHead;
    }
};
