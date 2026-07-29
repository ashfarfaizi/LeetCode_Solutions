class Solution {
public:
    vector<string> ans;
    string mp[10] = {
        "", "", "abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void build(int pos, string& digits, string& cur) {
        if (pos == digits.size()) {
            ans.push_back(cur);
            return;
        }

        string letters = mp[digits[pos] - '0'];

        for (char c : letters) {
            cur.push_back(c);
            build(pos + 1, digits, cur);
            cur.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        string cur;
        build(0, digits, cur);

        return ans;
    }
};