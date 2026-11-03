/*
 * Approach: Weave two chains in place. Walk with an odd pointer and an even
 * pointer, each skipping over the other's node, then attach the head of the
 * even chain to the tail of the odd chain.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};
