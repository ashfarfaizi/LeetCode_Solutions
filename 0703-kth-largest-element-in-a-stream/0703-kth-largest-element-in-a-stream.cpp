/*
 * Approach: Keep a min-heap holding only the k largest values seen so far. Its
 * top is then the kth largest; each add pushes the value and pops if the heap
 * grows beyond k.
 * Time: O(log k) per add (O(n log k) to build), Space: O(k)
 */
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k_(k) {
        for (int x : nums) add(x);
    }

    int add(int val) {
        heap_.push(val);
        if (static_cast<int>(heap_.size()) > k_) heap_.pop();
        return heap_.top();
    }

private:
    int k_;
    priority_queue<int, vector<int>, greater<int>> heap_;
};
