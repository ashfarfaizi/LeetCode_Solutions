#include <queue>

class MyStack {
private:
    std::queue<int> q;

public:
    MyStack() {
        // Constructor initializes an empty queue automatically
    }
    
    void push(int x) {
        // Step 1: Add the new element to the back
        q.push(x);
        
        // Step 2: Rotate the queue so the new element comes to the front
        int sz = q.size();
        for (int i = 0; i < sz - 1; ++i) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        // The top element of our stack is already at the front of the queue
        int topElement = q.front();
        q.pop();
        return topElement;
    }
    
    int top() {
        // Returns the element currently at the front
        return q.front();
    }
    
    bool empty() {
        // Returns true if queue has no elements
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
