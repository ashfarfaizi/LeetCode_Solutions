/*
 * Approach: two pointers over name and typed. When the characters agree,
 * advance both; otherwise the typed character must repeat the previous typed
 * character (a long press) or the input is invalid. All of name must be
 * consumed by the end.
 *
 * Time:  O(n + m)
 * Space: O(1)
 */
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        size_t i = 0;
        for (size_t j = 0; j < typed.size(); ++j) {
            if (i < name.size() && name[i] == typed[j]) {
                ++i;
            } else if (j == 0 || typed[j] != typed[j - 1]) {
                return false;
            }
        }
        return i == name.size();
    }
};
