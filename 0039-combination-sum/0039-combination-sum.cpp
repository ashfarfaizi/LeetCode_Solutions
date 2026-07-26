class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;

        sort(candidates.begin(), candidates.end());

        auto search = [&](auto&& self, int pos, int remaining) -> void {
            if (remaining == 0) {
                result.push_back(current);
                return;
            }

            for (int i = pos; i < (int)candidates.size(); ++i) {
                int value = candidates[i];

                if (value > remaining)
                    break;

                current.push_back(value);

                // i instead of i + 1 because the same number can be reused.
                self(self, i, remaining - value);

                current.pop_back();
            }
        };

        search(search, 0, target);
        return result;
    }
};