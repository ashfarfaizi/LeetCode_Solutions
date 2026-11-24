/*
 * Approach: Parse each side into (coefficient of x, constant) by scanning
 * signed terms. A term ending in 'x' adds to the coefficient (a bare "x" or
 * "-x" counts as 1 / -1); anything else adds to the constant. Move everything
 * to the left: a*x + b = 0. If a == 0 the answer depends on whether b == 0.
 *
 * Time:  O(n)
 * Space: O(1) besides the substrings for each side
 */
class Solution {
public:
    string solveEquation(string equation) {
        size_t eq = equation.find('=');
        auto [la, lb] = parse(equation.substr(0, eq));
        auto [ra, rb] = parse(equation.substr(eq + 1));
        int a = la - ra, b = rb - lb;  // a * x = b
        if (a == 0) return b == 0 ? "Infinite solutions" : "No solution";
        return "x=" + to_string(b / a);
    }

private:
    pair<int, int> parse(const string& s) {
        int coef = 0, cons = 0;
        size_t i = 0, n = s.size();
        while (i < n) {
            int sign = 1;
            if (s[i] == '+' || s[i] == '-') {
                if (s[i] == '-') sign = -1;
                ++i;
            }
            int val = 0;
            bool hasDigits = false;
            while (i < n && isdigit(static_cast<unsigned char>(s[i]))) {
                val = val * 10 + (s[i] - '0');
                hasDigits = true;
                ++i;
            }
            if (i < n && s[i] == 'x') {
                coef += sign * (hasDigits ? val : 1);
                ++i;
            } else {
                cons += sign * val;
            }
        }
        return {coef, cons};
    }
};
