class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* first = nullptr;
        ListNode* last = nullptr;

        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int total = carry;

            if (l1 != nullptr) {
                total += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                total += l2->val;
                l2 = l2->next;
            }

            ListNode* current = new ListNode(total % 10);
            carry = total / 10;

            if (first == nullptr) {
                first = current;
                last = current;
            } else {
                last->next = current;
                last = current;
            }
        }

        return first;
    }
};