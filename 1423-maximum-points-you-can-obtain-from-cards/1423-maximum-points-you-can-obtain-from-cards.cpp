/*
 * Approach: Whatever we take, the untouched cards form a contiguous window
 * of length n - k. Maximising the taken sum means minimising that window's
 * sum, found with a fixed-size sliding window.
 *
 * Time:  O(n)
 * Space: O(1)
 */
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size(), w = n - k;
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        int window = accumulate(cardPoints.begin(), cardPoints.begin() + w, 0);
        int best = window;
        for (int i = w; i < n; ++i) {
            window += cardPoints[i] - cardPoints[i - w];
            best = min(best, window);
        }
        return total - best;
    }
};
