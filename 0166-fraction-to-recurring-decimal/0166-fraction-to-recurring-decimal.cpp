/*
 * Approach: Long division. Handle the sign separately and work in 64-bit to
 * avoid overflow on INT_MIN. After the integer part, keep dividing the
 * remainder by the denominator; record the output position where each
 * remainder first appeared. A repeated remainder means the digits since that
 * position repeat, so insert '(' there and append ')'.
 * Time: O(d) where d is the denominator (at most d distinct remainders),
 * Space: O(d)
 */
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        string res;
        if ((numerator < 0) ^ (denominator < 0)) res += '-';
        long long n = llabs((long long)numerator), d = llabs((long long)denominator);
        res += to_string(n / d);
        long long rem = n % d;
        if (rem == 0) return res;
        res += '.';
        unordered_map<long long, size_t> seen;
        while (rem != 0) {
            auto it = seen.find(rem);
            if (it != seen.end()) {
                res.insert(it->second, "(");
                res += ')';
                break;
            }
            seen[rem] = res.size();
            rem *= 10;
            res += char('0' + rem / d);
            rem %= d;
        }
        return res;
    }
};
