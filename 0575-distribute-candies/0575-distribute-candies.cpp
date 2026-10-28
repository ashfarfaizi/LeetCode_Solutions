#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int distributeCandies(std::vector<int>& candyType) {
        // Find the number of unique candy types using an unordered_set
        std::unordered_set<int> uniqueCandies(candyType.begin(), candyType.end());
        
        // The doctor allows her to eat at most n / 2 candies
        int maxAllowed = candyType.size() / 2;
        
        // Return the minimum of unique types available and max allowed candies
        return std::min((int)uniqueCandies.size(), maxAllowed);
    }
};
