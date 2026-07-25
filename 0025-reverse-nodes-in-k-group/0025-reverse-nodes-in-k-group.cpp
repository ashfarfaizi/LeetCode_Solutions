class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k == 1)
            return head;

        ListNode anchor(0);
        anchor.next = head;

        ListNode* before = &anchor;

        while (true) {
            // Check whether a complete block of k nodes remains.
            ListNode* boundary = before;

            for (int step = 0; step < k && boundary != nullptr; ++step)
                boundary = boundary->next;

            if (boundary == nullptr)
                break;

            ListNode* after = boundary->next;
            ListNode* first = before->next;

            // Reverse exactly the current k-node block.
            ListNode* current = first;
            ListNode* previous = after;

            while (current != after) {
                ListNode* savedNext = current->next;
                current->next = previous;
                previous = current;
                current = savedNext;
            }

            // boundary is now the first node of the reversed block.
            before->next = boundary;

            // 'first' became the final node of this block.
            before = first;
        }

        return anchor.next;
    }
};