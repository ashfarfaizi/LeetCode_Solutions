class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = s.size();

        while (i < n && s[i] == ' ')
            ++i;

        int sign = 1;

        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-')
                sign = -1;
            ++i;
        }

        long long value = 0;

        while (i < n && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';

            if (value > (INT_MAX - digit) / 10LL)
                return sign == 1 ? INT_MAX : INT_MIN;

            value = value * 10 + digit;
            ++i;
        }

        value *= sign;

        if (value > INT_MAX)
            return INT_MAX;

        if (value < INT_MIN)
            return INT_MIN;

        return (int)value;
    }
};