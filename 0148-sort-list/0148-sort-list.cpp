/*
 * Approach: Bottom-up merge sort. Merge runs of size 1, 2, 4, ... by
 * repeatedly splitting off two runs of the current width and splicing the
 * merged result onto a tail pointer. No recursion, so extra space is O(1).
 * Time: O(n log n), Space: O(1)
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        int len = 0;
        for (ListNode* p = head; p; p = p->next) ++len;
        ListNode dummy(0);
        dummy.next = head;
        for (int width = 1; width < len; width *= 2) {
            ListNode* prev = &dummy;
            ListNode* cur = dummy.next;
            while (cur) {
                ListNode* left = cur;
                ListNode* right = split(left, width);
                cur = split(right, width);
                prev = merge(left, right, prev);
            }
        }
        return dummy.next;
    }

private:
    // Cut the list after n nodes; return the head of the remainder.
    ListNode* split(ListNode* head, int n) {
        for (int i = 1; head && i < n; ++i) head = head->next;
        if (!head) return nullptr;
        ListNode* rest = head->next;
        head->next = nullptr;
        return rest;
    }

    // Merge a and b after tail; return the new tail.
    ListNode* merge(ListNode* a, ListNode* b, ListNode* tail) {
        while (a && b) {
            if (a->val <= b->val) { tail->next = a; a = a->next; }
            else { tail->next = b; b = b->next; }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        while (tail->next) tail = tail->next;
        return tail;
    }
};
