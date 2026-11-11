/*
 * Approach: Union-Find with two candidates. First look for a node with two
 * parents; if found, remember both incoming edges (cand1 earlier, cand2
 * later) and skip cand2. Then union the remaining edges:
 *   - no cycle  -> cand2 is the answer;
 *   - cycle and there were two parents -> cand1 is the answer;
 *   - cycle and no node had two parents -> the edge that closed the cycle.
 * Time: O(n * alpha(n)), Space: O(n)
 */
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parentOf(n + 1, 0);
        vector<int> cand1, cand2;
        for (auto& e : edges) {
            if (parentOf[e[1]] != 0) {
                cand1 = {parentOf[e[1]], e[1]};
                cand2 = e;
            } else {
                parentOf[e[1]] = e[0];
            }
        }

        vector<int> root(n + 1);
        iota(root.begin(), root.end(), 0);
        function<int(int)> find = [&](int x) {
            return root[x] == x ? x : root[x] = find(root[x]);
        };
        for (auto& e : edges) {
            if (!cand2.empty() && e == cand2) continue;
            int a = find(e[0]), b = find(e[1]);
            if (a == b) return cand1.empty() ? e : cand1;
            root[b] = a;
        }
        return cand2;
    }
};
