/*
 * Approach: monotonic stack of (price, span) pairs with strictly decreasing
 * prices. A new price absorbs the spans of every stacked price that is not
 * greater than it, so each day is pushed and popped at most once.
 *
 * Time:  O(1) amortised per call to next()
 * Space: O(n)
 */
class StockSpanner {
public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;
        while (!st_.empty() && st_.back().first <= price) {
            span += st_.back().second;
            st_.pop_back();
        }
        st_.emplace_back(price, span);
        return span;
    }

private:
    vector<pair<int, int>> st_;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
