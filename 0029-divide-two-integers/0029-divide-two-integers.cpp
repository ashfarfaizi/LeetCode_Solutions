class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long a = dividend;
        long long b = divisor;

        bool negative = (a < 0) ^ (b < 0);

        if (a < 0) a = -a;
        if (b < 0) b = -b;

        long long quotient = 0;

        while (a >= b) {
            long long current = b;
            long long multiple = 1;

            while ((current << 1) <= a) {
                current <<= 1;
                multiple <<= 1;
            }

            a -= current;
            quotient += multiple;
        }

        if (negative)
            quotient = -quotient;

        return (int)quotient;
    }
};