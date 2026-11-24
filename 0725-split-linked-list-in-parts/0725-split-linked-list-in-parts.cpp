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
 * Approach: Count the length n. Each part gets n / k nodes and the first
 * n % k parts get one extra. Walk the list, cutting after each part's last
 * node.
 *
 * Time:  O(n + k)
 * Space: O(k) for the output
 */
class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = 0;
        for (ListNode* p = head; p; p = p->next) ++n;
        int base = n / k, extra = n % k;
        vector<ListNode*> parts(k, nullptr);
        ListNode* cur = head;
        for (int i = 0; i < k && cur; ++i) {
            parts[i] = cur;
            int len = base + (i < extra ? 1 : 0);
            for (int j = 1; j < len; ++j) cur = cur->next;
            ListNode* next = cur->next;
            cur->next = nullptr;
            cur = next;
        }
        return parts;
    }
};
