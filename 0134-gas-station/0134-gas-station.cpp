class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total_surplus = 0; // Tracks if a global solution exists
        int current_tank = 0;   // Tracks gas level for the current starting point
        int start_index = 0;    // Candidate starting station index
        
        for (int i = 0; i < gas.size(); i++) {
            int net_fuel = gas[i] - cost[i];
            total_surplus += net_fuel;
            current_tank += net_fuel;
            
            // If tank drops below 0, station 'i' cannot be reached from 'start_index'
            if (current_tank < 0) {
                // Reset tank and try the next station as the starting point
                start_index = i + 1;
                current_tank = 0;
            }
        }
        
        // If the total gas is less than total cost, return -1; otherwise, the candidate is guaranteed valid
        return (total_surplus < 0) ? -1 : start_index;
    }
};
