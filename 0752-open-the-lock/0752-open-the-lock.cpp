/*
 * Approach: Breadth-first search over the 10^4 lock states, treating dead ends
 * as pre-visited. Each state has 8 neighbours (4 wheels x up/down). The BFS
 * level at which the target is popped is the minimum number of turns.
 * Time: O(10^4 * 8), Space: O(10^4)
 */
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        vector<bool> seen(10000, false);
        for (const string& d : deadends) seen[stoi(d)] = true;
        if (seen[0]) return -1;

        int goal = stoi(target);
        const int pow10[4] = {1, 10, 100, 1000};
        queue<int> q;
        q.push(0);
        seen[0] = true;
        for (int steps = 0; !q.empty(); ++steps) {
            for (int sz = q.size(); sz > 0; --sz) {
                int cur = q.front();
                q.pop();
                if (cur == goal) return steps;
                for (int w = 0; w < 4; ++w) {
                    int digit = cur / pow10[w] % 10;
                    for (int delta : {1, 9}) {
                        int next = cur + ((digit + delta) % 10 - digit) * pow10[w];
                        if (!seen[next]) {
                            seen[next] = true;
                            q.push(next);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
