/*
 * Approach: Union-Find over the n cities. Every direct connection merges two
 * components; each successful union reduces the province count by one.
 * Path compression + union by size keep operations near O(1).
 * Time: O(n^2 * α(n)), Space: O(n)
 */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
        int provinces = n;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (isConnected[i][j] && unite(i, j)) --provinces;
        return provinces;
    }

private:
    vector<int> parent, size;

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};
