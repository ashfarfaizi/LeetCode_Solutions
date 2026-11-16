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
 * Approach: Put nums in a hash set, then walk the list. A component ends at
 * a node whose value is in the set while the next node is missing or not in
 * the set, so count those component ends.
 * Time: O(n + m), Space: O(m) for the set
 */
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> in(nums.begin(), nums.end());
        int components = 0;
        for (ListNode* cur = head; cur; cur = cur->next)
            if (in.count(cur->val) && (!cur->next || !in.count(cur->next->val)))
                ++components;
        return components;
    }
};
