/*
 * Approach: greedy with an ordered count map. The smallest remaining card
 * must start a group, so repeatedly take the smallest value x with count c
 * and consume c copies of each of x, x+1, ..., x+groupSize-1. If any of
 * those has fewer than c copies left, the hand can't be split.
 *
 * Time:  O(n log n)
 * Space: O(n)
 */
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;
        map<int, int> count;
        for (int card : hand) ++count[card];
        for (auto it = count.begin(); it != count.end(); ++it) {
            int start = it->first, need = it->second;
            if (need == 0) continue;
            for (int k = 0; k < groupSize; ++k) {
                auto cur = count.find(start + k);
                if (cur == count.end() || cur->second < need) return false;
                cur->second -= need;
            }
        }
        return true;
    }
};
