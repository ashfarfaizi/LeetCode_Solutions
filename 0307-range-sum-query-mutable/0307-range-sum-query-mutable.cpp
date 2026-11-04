/*
 * Approach: Fenwick (binary indexed) tree over the array. Each tree slot i
 * stores the sum of the block ending at i of length lowbit(i). update adds the
 * delta from the old value along i += lowbit(i); a prefix sum walks
 * i -= lowbit(i); a range sum is the difference of two prefixes. The tree is
 * built in O(n) by pushing each slot into its parent once.
 * Time: O(n) build, O(log n) update and sumRange, Space: O(n)
 */
class NumArray {
public:
    NumArray(vector<int>& nums) : vals(nums), tree(nums.size() + 1, 0) {
        int n = nums.size();
        for (int i = 1; i <= n; ++i) {
            tree[i] += nums[i - 1];
            int parent = i + (i & -i);
            if (parent <= n) tree[parent] += tree[i];
        }
    }

    void update(int index, int val) {
        int delta = val - vals[index];
        vals[index] = val;
        for (int i = index + 1; i < (int)tree.size(); i += i & -i) tree[i] += delta;
    }

    int sumRange(int left, int right) {
        return prefix(right + 1) - prefix(left);
    }

private:
    vector<int> vals;
    vector<int> tree;

    int prefix(int i) {  // sum of the first i elements
        int s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
};
