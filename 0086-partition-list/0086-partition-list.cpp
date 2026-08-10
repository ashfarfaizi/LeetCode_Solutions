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
    ListNode* partition(ListNode* head, int x) {
        // Dummy head nodes to serve as fixed anchor points for both partitions
        ListNode* lessHead = new ListNode(0);
        ListNode* greaterHead = new ListNode(0);

        // Tracking pointers to append new elements to the tail of each partition
        ListNode* lessTail = lessHead;
        ListNode* greaterTail = greaterHead;

        // Traverse the original linked list sequentially
        while (head != nullptr) {
            if (head->val < x) {
                lessTail->next = head;
                lessTail = lessTail->next;
            } else {
                greaterTail->next = head;
                greaterTail = greaterTail->next;
            }
            head = head->next;
        }

        // Prevent memory cycle bugs by truncating the next pointer of the final element
        greaterTail->next = nullptr;

        // Stitch the two independent partition segments together
        lessTail->next = greaterHead->next;

        // Save the real head node pointer before deallocating structural dummy memory
        ListNode* partitionedHead = lessHead->next;
        
        delete lessHead;
        delete greaterHead;

        return partitionedHead;
    }
};
