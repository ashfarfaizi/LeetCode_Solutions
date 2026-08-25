#include <string>

class Solution {
public:
    int compareVersion(std::string version1, std::string version2) {
        int i = 0, j = 0;
        int n1 = version1.length();
        int n2 = version2.length();

        while (i < n1 || j < n2) {
            int num1 = 0;
            int num2 = 0;

            // Extract numeric value for version1's current revision
            while (i < n1 && version1[i] != '.') {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }

            // Extract numeric value for version2's current revision
            while (j < n2 && version2[j] != '.') {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }

            // Compare the parsed revision values
            if (num1 < num2) return -1;
            if (num1 > num2) return 1;

            // Move pointers past the dot character '.'
            i++;
            j++;
        }

        return 0;
    }
};
