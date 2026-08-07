#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
private:
    struct PrimeCounts {
        int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
    };

    PrimeCounts getFactors(long long n) {
        PrimeCounts pc;
        while (n % 2 == 0) { pc.p2++; n /= 2; }
        while (n % 3 == 0) { pc.p3++; n /= 3; }
        while (n % 5 == 0) { pc.p5++; n /= 5; }
        while (n % 7 == 0) { pc.p7++; n /= 7; }
        if (n > 1) return {-1, -1, -1, -1};
        return pc;
    }

    const int digitFactors[10][4] = {
        {0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {2,0,0,0},
        {0,0,1,0}, {1,1,0,0}, {0,0,0,1}, {3,0,0,0}, {0,2,0,0}
    };

    int dp_memo[65][45];

    void initDP() {
        for (int i = 0; i < 65; ++i) {
            for (int j = 0; j < 45; ++j) {
                dp_memo[i][j] = 1e9;
            }
        }
        dp_memo[0][0] = 0;

        vector<pair<int, int>> choices = {{1,0}, {0,1}, {2,0}, {1,1}, {3,0}, {0,2}};

        for (int i = 0; i < 65; ++i) {
            for (int j = 0; j < 45; ++j) {
                if (dp_memo[i][j] == 1e9) continue;
                for (auto& choice : choices) {
                    int ni = min(64, i + choice.first);
                    int nj = min(44, j + choice.second);
                    dp_memo[ni][nj] = min(dp_memo[ni][nj], dp_memo[i][j] + 1);
                }
            }
        }
    }

    int exactSlotsFor23(int r2, int r3) {
        if (r2 <= 0 && r3 <= 0) return 0;
        r2 = min(64, max(0, r2));
        r3 = min(44, max(0, r3));
        return dp_memo[r2][r3];
    }

    bool canSatisfy(int remLen, int r2, int r3, int r5, int r7) {
        r5 = max(0, r5); r7 = max(0, r7);
        int req = r5 + r7 + exactSlotsFor23(r2, r3);
        return req <= remLen;
    }

    // Completely reconstructed digit-by-digit optimal generator
    string matchSuffix(int remLen, int r2, int r3, int r5, int r7) {
        r2 = max(0, r2); r3 = max(0, r3); r5 = max(0, r5); r7 = max(0, r7);
        
        int absolute_min_slots = r5 + r7 + exactSlotsFor23(r2, r3);
        remLen = max(remLen, absolute_min_slots);

        string s = "";
        s.reserve(remLen);
        
        // Greedily choose the absolute smallest digit from 1 to 9 for each available slot
        for (int step = 0; step < remLen; ++step) {
            for (int d = 1; d <= 9; ++d) {
                int n2 = max(0, r2 - digitFactors[d][0]);
                int n3 = max(0, r3 - digitFactors[d][1]);
                int n5 = max(0, r5 - digitFactors[d][2]);
                int n7 = max(0, r7 - digitFactors[d][3]);
                
                int spaces_left = remLen - step - 1;
                if (canSatisfy(spaces_left, n2, n3, n5, n7)) {
                    s += to_string(d);
                    r2 = n2; r3 = n3; r5 = n5; r7 = n7;
                    break;
                }
            }
        }
        return s;
    }

public:
    string smallestNumber(string num, long long t) {
        initDP();

        PrimeCounts target = getFactors(t);
        if (target.p2 == -1) return "-1";

        int n = num.length();
        vector<PrimeCounts> pref(n + 1);
        
        int firstZero = -1;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i];
            if (num[i] == '0') {
                if (firstZero == -1) firstZero = i;
                continue;
            }
            int d = num[i] - '0';
            pref[i + 1].p2 += digitFactors[d][0];
            pref[i + 1].p3 += digitFactors[d][1];
            pref[i + 1].p5 += digitFactors[d][2];
            pref[i + 1].p7 += digitFactors[d][3];
        }

        if (firstZero == -1) {
            if (pref[n].p2 >= target.p2 && pref[n].p3 >= target.p3 &&
                pref[n].p5 >= target.p5 && pref[n].p7 >= target.p7) {
                return num;
            }
        }

        int limit = (firstZero == -1) ? n - 1 : firstZero;
        for (int i = limit; i >= 0; --i) {
            int startDigit = (num[i] - '0') + 1;
            for (int d = startDigit; d <= 9; ++d) {
                int remLen = n - 1 - i;
                int req2 = target.p2 - pref[i].p2 - digitFactors[d][0];
                int req3 = target.p3 - pref[i].p3 - digitFactors[d][1];
                int req5 = target.p5 - pref[i].p5 - digitFactors[d][2];
                int req7 = target.p7 - pref[i].p7 - digitFactors[d][3];

                if (canSatisfy(remLen, req2, req3, req5, req7)) {
                    string ans = num.substr(0, i) + to_string(d);
                    ans += matchSuffix(remLen, req2, req3, req5, req7);
                    return ans;
                }
            }
        }

        return matchSuffix(n + 1, target.p2, target.p3, target.p5, target.p7);
    }
};
