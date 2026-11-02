/*
 * Approach: Interleave copies (A -> A' -> B -> B' ...), set each copy's random
 * to original->random->next, then unweave the two lists. Avoids a hash map.
 * Time: O(n), Space: O(1) extra (excluding the output)
 */
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        for (Node* cur = head; cur; cur = cur->next->next) {
            Node* copy = new Node(cur->val);
            copy->next = cur->next;
            cur->next = copy;
        }
        for (Node* cur = head; cur; cur = cur->next->next)
            cur->next->random = cur->random ? cur->random->next : nullptr;
        Node* newHead = head->next;
        for (Node* cur = head; cur; cur = cur->next) {
            Node* copy = cur->next;
            cur->next = copy->next;
            copy->next = copy->next ? copy->next->next : nullptr;
        }
        return newHead;
    }
};
