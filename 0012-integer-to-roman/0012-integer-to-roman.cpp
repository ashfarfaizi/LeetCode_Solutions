class Solution {
public:
    string intToRoman(int num) {
        const int value[] = {
            1000, 900, 500, 400,
            100, 90, 50, 40,
            10, 9, 5, 4, 1
        };

        const string symbol[] = {
            "M", "CM", "D", "CD",
            "C", "XC", "L", "XL",
            "X", "IX", "V", "IV", "I"
        };

        string roman;

        for (int i = 0; i < 13; ++i) {
            while (num >= value[i]) {
                roman += symbol[i];
                num -= value[i];
            }
        }

        return roman;
    }
};