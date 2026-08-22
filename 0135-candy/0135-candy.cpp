class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n <= 1) return n;
        
        // Step 1: Every child initially gets at least 1 candy
        vector<int> candies(n, 1);
        
        // Step 2: Left-to-Right pass (checking left neighbors)
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        
        // Step 3: Right-to-Left pass (checking right neighbors)
        int total_candies = candies[n - 1]; // Seed with the last element
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
            total_candies += candies[i]; // Simultaneously accumulate total
        }
        
        return total_candies;
    }
};
