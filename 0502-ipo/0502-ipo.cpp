#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
        int n = profits.size();
        std::vector<std::pair<int, int>> projects(n);
        
        // Step 1: Pair up capital and profit
        for (int i = 0; i < n; ++i) {
            projects[i] = {capital[i], profits[i]};
        }
        
        // Step 2: Sort projects based on their minimum capital requirement
        std::sort(projects.begin(), projects.end());
        
        // Max-heap to store profits of all affordable projects
        std::priority_queue<int> maxProfitHeap;
        int i = 0;
        
        // Step 3: Loop up to k times to pick at most k projects
        while (k > 0) {
            // Push all projects we can afford with our current capital into the heap
            while (i < n && projects[i].first <= w) {
                maxProfitHeap.push(projects[i].second);
                i++;
            }
            
            // If we can't afford any project, we can't proceed further
            if (maxProfitHeap.empty()) {
                break;
            }
            
            // Pick the project with the maximum profit
            w += maxProfitHeap.top();
            maxProfitHeap.pop();
            
            k--;
        }
        
        return w;
    }
};
