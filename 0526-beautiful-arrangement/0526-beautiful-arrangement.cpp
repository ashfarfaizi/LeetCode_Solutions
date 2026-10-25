class Solution {
private:
    int count = 0;

    void backtrack(int n, int index, vector<bool>& visited) {
        // Base case: If we successfully placed numbers at all positions from 1 to n
        if (index > n) {
            count++;
            return;
        }

        // Try placing every available number 'i' at the current 'index'
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && (i % index == 0 || index % i == 0)) {
                visited[i] = true;         // Choose
                backtrack(n, index + 1, visited); // Explore
                visited[i] = false;        // Unchoose (Backtrack)
            }
        }
    }

public:
    int countArrangement(int n) {
        vector<bool> visited(n + 1, false);
        backtrack(n, 1, visited);
        return count;
    }
};
