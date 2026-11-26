/*
 * Approach: simulate the reveal process on positions instead of values.
 * A queue of indices 0..n-1 tells us which position is revealed next; give
 * that position the next smallest card, then rotate the following index to
 * the back of the queue.
 * Time: O(n log n) for the sort, Space: O(n)
 */
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        deque<int> idx;
        for (int i = 0; i < n; ++i) idx.push_back(i);
        vector<int> res(n);
        for (int card : deck) {
            res[idx.front()] = card;
            idx.pop_front();
            if (!idx.empty()) {
                idx.push_back(idx.front());
                idx.pop_front();
            }
        }
        return res;
    }
};
