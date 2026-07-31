class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string current;

        function<void(int, int)> build = [&](int open, int close) {
            if (current.size() == 2 * n) {
                ans.push_back(current);
                return;
            }

            if (open < n) {
                current.push_back('(');
                build(open + 1, close);
                current.pop_back();
            }

            if (close < open) {
                current.push_back(')');
                build(open, close + 1);
                current.pop_back();
            }
        };

        build(0, 0);
        return ans;
    }
};