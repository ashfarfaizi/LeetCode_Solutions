class Solution {
public:
    long long limit = 1000001;

    long long ways(vector<int>& cnt, int remaining) {
        long long res = 1;
        int used = 0;

        for (int c : cnt) {
            for (int j = 1; j <= c; ++j) {
                long long num = used + j;
                long long den = j;

                long long g = gcd(num, den);
                num /= g;
                den /= g;

                g = gcd(res, den);
                res /= g;
                den /= g;

                if (res > limit / num)
                    return limit;

                res *= num;
                res /= den;

                if (res >= limit)
                    return limit;
            }
            used += c;
        }

        return res;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        char middle = 0;
        vector<int> half(26);

        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2)
                middle = char('a' + i);

            half[i] = freq[i] / 2;
        }

        int len = s.size() / 2;

        if (ways(half, len) < k)
            return "";

        string left;

        for (int pos = 0; pos < len; ++pos) {
            for (int c = 0; c < 26; ++c) {
                if (half[c] == 0)
                    continue;

                half[c]--;

                long long cnt = ways(half, len - pos - 1);

                if (k > cnt) {
                    k -= cnt;
                    half[c]++;
                } else {
                    left.push_back(char('a' + c));
                    break;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (middle)
            return left + string(1, middle) + right;

        return left + right;
    }
};