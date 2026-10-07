#include <stack>

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        std::stack<int> s1;
        std::stack<int> s2;
        
        // Push all values of l1 into stack s1
        while (l1 != nullptr) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        
        // Push all values of l2 into stack s2
        while (l2 != nullptr) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        
        int carry = 0;
        ListNode* head = nullptr;
        
        // Process both stacks from the least significant digit
        while (!s1.empty() || !s2.empty() || carry != 0) {
            int sum = carry;
            
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }
            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }
            
            carry = sum / 10;
            
            // Build the result list forwards (insert at head)
            ListNode* newNode = new ListNode(sum % 10);
            newNode->next = head;
            head = newNode;
        }
        
        return head;
    }
};
