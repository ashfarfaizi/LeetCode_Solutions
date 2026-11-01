/*
 * Approach: Use a dummy head so removing the first node needs no special
 * case, then unlink every node whose value equals val.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0, head);
        ListNode* cur = &dummy;
        while (cur->next) {
            if (cur->next->val == val) cur->next = cur->next->next;
            else cur = cur->next;
        }
        return dummy.next;
    }
};
