class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        int n = nums.size();

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            if (nums[i] > 0)
                break;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                long long sum = (long long)nums[i] 
                              + nums[left] 
                              + nums[right];

                if (sum == 0) {
                    ans.push_back({nums[i], nums[left], nums[right]});

                    int leftValue = nums[left];
                    int rightValue = nums[right];

                    while (left < right && nums[left] == leftValue)
                        ++left;

                    while (left < right && nums[right] == rightValue)
                        --right;
                }
                else if (sum < 0) {
                    ++left;
                }
                else {
                    --right;
                }
            }
        }

        return ans;
    }
};