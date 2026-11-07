/*
 * Approach: Two queues of senator indices, one per party. Repeatedly compare
 * the fronts: the earlier senator bans the other and re-enters the next round
 * at index + n, so turn order is preserved. The party whose queue survives
 * wins.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        queue<int> radiant, dire;
        for (int i = 0; i < n; ++i)
            (senate[i] == 'R' ? radiant : dire).push(i);
        while (!radiant.empty() && !dire.empty()) {
            int r = radiant.front(), d = dire.front();
            radiant.pop();
            dire.pop();
            if (r < d) radiant.push(r + n);
            else dire.push(d + n);
        }
        return radiant.empty() ? "Dire" : "Radiant";
    }
};
