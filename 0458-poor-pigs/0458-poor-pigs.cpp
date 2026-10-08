#include <cmath>

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // Calculate how many distinct outcomes one pig can produce
        int states = (minutesToTest / minutesToDie) + 1;
        
        int pigs = 0;
        long long current_buckets_covered = 1;
        
        // Find the minimum x such that states^x >= buckets
        while (current_buckets_covered < buckets) {
            current_buckets_covered *= states;
            pigs++;
        }
        
        return pigs;
    }
};
