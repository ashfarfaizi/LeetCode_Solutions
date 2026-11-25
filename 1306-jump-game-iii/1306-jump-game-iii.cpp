/*
 * Approach: BFS over indices. Each index has at most two neighbours; mark
 * an index as visited by negating its value (values are non-negative, and
 * a visited zero is already the answer).
 *
 * Time:  O(n)
 * Space: O(n) for the queue
 */
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            if (arr[i] == 0) return true;
            if (arr[i] < 0) continue;
            int step = arr[i];
            arr[i] = -arr[i];
            if (i + step < n) q.push(i + step);
            if (i - step >= 0) q.push(i - step);
        }
        return false;
    }
};
