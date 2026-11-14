/*
 * Approach: Mark every jewel character in a 128-entry lookup table, then count
 * the stones whose character is marked.
 * Time: O(J + S), Space: O(1)
 */
class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        array<bool, 128> isJewel{};
        for (char c : jewels) isJewel[static_cast<unsigned char>(c)] = true;
        int count = 0;
        for (char c : stones) count += isJewel[static_cast<unsigned char>(c)];
        return count;
    }
};
