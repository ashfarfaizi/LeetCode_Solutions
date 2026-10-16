#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::vector<std::string> findRelativeRanks(std::vector<int>& score) {
        int n = score.size();
        std::vector<std::pair<int, int>> sorted_scores(n);
        
        // Step 1: Pair up each score with its original index
        for (int i = 0; i < n; ++i) {
            sorted_scores[i] = {score[i], i};
        }
        
        // Step 2: Sort in descending order based on score
        std::sort(sorted_scores.begin(), sorted_scores.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
        
        std::vector<std::string> answer(n);
        
        // Step 3: Map placements back to original positions
        for (int i = 0; i < n; ++i) {
            int original_index = sorted_scores[i].second;
            
            if (i == 0) {
                answer[original_index] = "Gold Medal";
            } else if (i == 1) {
                answer[original_index] = "Silver Medal";
            } else if (i == 2) {
                answer[original_index] = "Bronze Medal";
            } else {
                answer[original_index] = std::to_string(i + 1);
            }
        }
        
        return answer;
    }
};
