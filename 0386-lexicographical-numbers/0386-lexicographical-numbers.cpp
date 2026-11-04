/*
 * Approach: Iterative preorder walk of the implicit 10-ary trie of numbers.
 * From cur, go to the first child cur*10 if it is <= n. Otherwise move to the
 * next sibling cur+1, first climbing up (cur /= 10) while cur ends in 9 or
 * cur+1 would exceed n.
 * Time: O(n), Space: O(1) besides the output
 */
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        res.reserve(n);
        long long cur = 1;
        for (int i = 0; i < n; ++i) {
            res.push_back((int)cur);
            if (cur * 10 <= n) {
                cur *= 10;
            } else {
                while (cur % 10 == 9 || cur + 1 > n) cur /= 10;
                ++cur;
            }
        }
        return res;
    }
};
