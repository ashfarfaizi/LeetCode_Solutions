#include <algorithm>

class Solution {
public:
    int findKthNumber(int n, int k) {
        long long curr = 1;
        k -= 1; // We start at 1, so we need k - 1 more steps
        
        while (k > 0) {
            long long steps = countSteps(n, curr, curr + 1);
            
            // If the target is not in the current prefix subtree
            if (steps <= k) {
                k -= steps;
                curr += 1; // Move to the next sibling
            } 
            // If the target is within the current prefix subtree
            else {
                k -= 1;
                curr *= 10; // Move down to the first child
            }
        }
        
        return curr;
    }

private:
    long long countSteps(long long n, long long n1, long long n2) {
        long long steps = 0;
        while (n1 <= n) {
            // Count valid nodes at the current tree level
            steps += std::min(n + 1, n2) - n1;
            n1 *= 10;
            n2 *= 10;
        }
        return steps;
    }
};
