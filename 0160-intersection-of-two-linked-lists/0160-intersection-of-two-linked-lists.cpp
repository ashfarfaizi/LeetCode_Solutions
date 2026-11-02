/*
 * Approach: Two pointers walk both lists; when one reaches the end it jumps
 * to the other list's head. Both travel lenA + lenB steps, so they meet at
 * the intersection node (or both become nullptr together).
 * Time: O(m + n), Space: O(1)
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *a = headA, *b = headB;
        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        return a;
    }
};
