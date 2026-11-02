/*
 * Approach: Push onto an input stack; pop/peek from an output stack, refilling
 * it from the input stack only when it is empty. Each element moves at most
 * once, giving amortized O(1) operations.
 * Time: amortized O(1) per op, Space: O(n)
 */
class MyQueue {
    stack<int> in, out;
    void shift() {
        if (out.empty())
            while (!in.empty()) { out.push(in.top()); in.pop(); }
    }
public:
    MyQueue() {}

    void push(int x) { in.push(x); }

    int pop() {
        shift();
        int x = out.top();
        out.pop();
        return x;
    }

    int peek() {
        shift();
        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }
};
