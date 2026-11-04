/*
 * Approach: Two heaps. `low` is a max-heap holding the smaller half and
 * `high` a min-heap holding the larger half, with low allowed to be at most
 * one element bigger. Each insert goes through low into high and is moved
 * back if high grows larger, which keeps both the ordering and size
 * invariants. The median is low's top, or the mean of both tops.
 * Time: O(log n) addNum, O(1) findMedian, Space: O(n)
 */
class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        low.push(num);
        high.push(low.top());
        low.pop();
        if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }

    double findMedian() {
        if (low.size() > high.size()) return low.top();
        return ((double)low.top() + high.top()) / 2.0;
    }

private:
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;
};
