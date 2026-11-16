/*
 * Approach: Sort jobs by difficulty and workers by ability. Sweep workers in
 * increasing ability with a pointer over jobs, keeping the best profit among
 * every job the current worker can handle; each worker takes that best.
 * Time: O(n log n + m log m), Space: O(n)
 */
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        vector<pair<int, int>> jobs(n);
        for (int i = 0; i < n; ++i) jobs[i] = {difficulty[i], profit[i]};
        sort(jobs.begin(), jobs.end());
        sort(worker.begin(), worker.end());
        int total = 0, best = 0, j = 0;
        for (int ability : worker) {
            while (j < n && jobs[j].first <= ability) best = max(best, jobs[j++].second);
            total += best;
        }
        return total;
    }
};
