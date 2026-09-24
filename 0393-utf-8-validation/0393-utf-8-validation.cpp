#include <vector>

using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int remaining_bytes = 0; // Number of continuation bytes expected

        for (int num : data) {
            // If we are not expecting continuation bytes, this is a new character's starting byte
            if (remaining_bytes == 0) {
                if ((num >> 7) == 0b0) {
                    remaining_bytes = 0; // 1-byte character
                } else if ((num >> 5) == 0b110) {
                    remaining_bytes = 1; // 2-byte character (requires 1 continuation byte)
                } else if ((num >> 4) == 0b1110) {
                    remaining_bytes = 2; // 3-byte character (requires 2 continuation bytes)
                } else if ((num >> 3) == 0b11110) {
                    remaining_bytes = 3; // 4-byte character (requires 3 continuation bytes)
                } else {
                    return false;        // Invalid prefix
                }
            } else {
                // If we are expecting a continuation byte, it MUST start with bits '10'
                if ((num >> 6) != 0b10) {
                    return false;
                }
                remaining_bytes--;
            }
        }

        // If remaining_bytes is 0, all characters were completely validated
        return remaining_bytes == 0;
    }
};
