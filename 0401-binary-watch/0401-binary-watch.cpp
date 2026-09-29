#include <vector>
#include <string>

class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        
        // Loop through all possible hours and minutes
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                // Count total set bits (LEDs turned on)
                if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                    // Format minutes with leading zero if needed
                    string minute_str = (m < 10) ? "0" + to_string(m) : to_string(m);
                    result.push_back(to_string(h) + ":" + minute_str);
                }
            }
        }
        
        return result;
    }
};
