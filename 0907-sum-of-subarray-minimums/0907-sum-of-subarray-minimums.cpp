/*
 * Approach: count each element's contribution as the minimum. With monotonic
 * stacks find, for every i, how far it extends left (previous strictly
 * smaller element) and right (next smaller-or-equal element); arr[i] is the
 * minimum of left * right subarrays. The strict/non-strict split makes ties
 * counted exactly once.
 *
 * Time:  O(n)
 * Space: O(n)
 */
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const long long MOD = 1'000'000'007;
        int n = arr.size();
        vector<int> left(n), right(n);
        vector<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && arr[st.back()] >= arr[i]) st.pop_back();
            left[i] = st.empty() ? i + 1 : i - st.back();
            st.push_back(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && arr[st.back()] > arr[i]) st.pop_back();
            right[i] = st.empty() ? n - i : st.back() - i;
            st.push_back(i);
        }
        long long total = 0;
        for (int i = 0; i < n; ++i)
            total = (total + (long long)arr[i] * left[i] % MOD * right[i]) % MOD;
        return (int)total;
    }
};
