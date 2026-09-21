class Solution {
private:
    vector<int> values;

public:
    Solution(ListNode* head) {
        while (head != nullptr) {
            values.push_back(head->val);
            head = head->next;
        }
    }
    
    int getRandom() {
        // Pick a random index from 0 to values.size() - 1
        int idx = rand() % values.size();
        return values[idx];
    }
};
