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
/*
 * Approach: Find the middle with slow/fast pointers, reversing the first
 * half in place as slow advances. Then walk the reversed first half and the
 * second half together; paired nodes are exactly the twins.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int pairSum(ListNode* head) {
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while (fast && fast->next) {
            fast = fast->next->next;
            ListNode* next = slow->next;
            slow->next = prev;
            prev = slow;
            slow = next;
        }
        int best = 0;
        for (; prev && slow; prev = prev->next, slow = slow->next) {
            best = max(best, prev->val + slow->val);
        }
        return best;
    }
};
