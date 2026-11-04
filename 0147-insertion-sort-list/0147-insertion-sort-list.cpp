/*
 * Approach: Keep a dummy-headed sorted list. For each node taken from the
 * input, walk the sorted list to find the first node with a larger value and
 * splice it in before. If the node is not smaller than the last inserted one,
 * resume the scan from there instead of the head (helps on nearly-sorted input).
 * Time: O(n^2) worst case, Space: O(1)
 */
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(0);
        ListNode* prev = &dummy;
        while (head) {
            ListNode* next = head->next;
            if (prev != &dummy && prev->val > head->val) prev = &dummy;
            while (prev->next && prev->next->val <= head->val) prev = prev->next;
            head->next = prev->next;
            prev->next = head;
            head = next;
        }
        return dummy.next;
    }
};
