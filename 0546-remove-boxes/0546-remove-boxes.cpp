class Solution {
    int memo[100][100][100];

    int dp(vector<int>& boxes, int l, int r, int k) {
        if (l > r) return 0;
        if (memo[l][r][k] != 0) return memo[l][r][k];

        int l_orig = l, k_orig = k;
        while (l + 1 <= r && boxes[l + 1] == boxes[l]) {
            l++;
            k++;
        }

        int res = (k + 1) * (k + 1) + dp(boxes, l + 1, r, 0);

        for (int m = l + 1; m <= r; m++) {
            if (boxes[m] == boxes[l]) {
                res = max(res, dp(boxes, l + 1, m - 1, 0) + dp(boxes, m, r, k + 1));
            }
        }

        return memo[l_orig][r][k_orig] = res;
    }

public:
    int removeBoxes(vector<int>& boxes) {
        memset(memo, 0, sizeof(memo));
        return dp(boxes, 0, boxes.size() - 1, 0);
    }
};
