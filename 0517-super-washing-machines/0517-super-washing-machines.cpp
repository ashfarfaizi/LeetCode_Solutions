class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int total_dresses = 0;
        for (int dresses : machines) {
            total_dresses += dresses;
        }
        
        int n = machines.size();
        if (total_dresses % n != 0) return -1;
        
        int target = total_dresses / n;
        int max_moves = 0;
        int current_balance = 0;
        
        for (int dresses : machines) {
            current_balance += dresses - target;
            max_moves = max({max_moves, abs(current_balance), dresses - target});
        }
        
        return max_moves;
    }
};
