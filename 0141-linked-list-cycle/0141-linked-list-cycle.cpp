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
    bool hasCycle(ListNode *head) {
        // Base case: an empty list or single node cannot have a cycle
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        // Traverse the list
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // Move 1 step
            fast = fast->next->next;    // Move 2 steps
            
            // If they meet, a cycle exists
            if (slow == fast) {
                return true;
            }
        }
        
        // Fast pointer reached the end, so no cycle
        return false;
    }
};
