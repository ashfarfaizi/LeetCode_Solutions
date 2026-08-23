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
    ListNode *detectCycle(ListNode *head) {
        // Base case: empty list or single element cannot have a cycle
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        
        ListNode *slow = head;
        ListNode *fast = head;
        bool hasCycle = false;
        
        // Phase 1: Determine if a cycle exists
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        // If no cycle was detected, return null
        if (!hasCycle) {
            return nullptr;
        }
        
        // Phase 2: Find the entry point of the cycle
        // Reset fast to head; move both pointers 1 step at a time
        fast = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow; // Both meet at the start of the cycle
    }
};
