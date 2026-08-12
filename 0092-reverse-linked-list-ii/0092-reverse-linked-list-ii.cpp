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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // Edge case: if the list is empty or left equals right, no reversal is needed
        if (!head || left == right) {
            return head;
        }
        
        // A dummy node helps manage edge cases smoothly, such as when left = 1 (reversing from the head)
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;
        
        // Move the 'prev' pointer to the node exactly before the sublist starts reversing
        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }
        
        // 'curr' marks the start of the sublist to be reversed
        ListNode* curr = prev->next;
        
        // Perform an in-place link readjustment for the nodes between left and right positions
        for (int i = 0; i < right - left; ++i) {
            ListNode* nextNode = curr->next;
            curr->next = nextNode->next;
            nextNode->next = prev->next;
            prev->next = nextNode;
        }
        
        return dummy.next;
    }
};
