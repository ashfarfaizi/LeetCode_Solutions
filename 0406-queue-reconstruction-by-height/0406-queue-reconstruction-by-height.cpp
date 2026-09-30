#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // Step 1: Sort people
        // Custom comparator: Descending by height, ascending by k if heights match
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] < b[1];
            }
            return a[0] > b[0];
        });
        
        vector<vector<int>> queue;
        
        // Step 2: Insert into the result vector at index k
        for (const auto& person : people) {
            queue.insert(queue.begin() + person[1], person);
        }
        
        return queue;
    }
};
