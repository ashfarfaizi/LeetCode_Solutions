/*
 * Approach: Single pass. Count total 'A's and track the current run of
 * consecutive 'L's; fail as soon as absences reach 2 or a run reaches 3.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool checkRecord(string s) {
        int absences = 0, lateRun = 0;
        for (char c : s) {
            if (c == 'A' && ++absences >= 2) return false;
            lateRun = (c == 'L') ? lateRun + 1 : 0;
            if (lateRun >= 3) return false;
        }
        return true;
    }
};
