#include <vector>
#include <stack>

class NestedIterator {
private:
    // Store pairs of (begin iterator, end iterator) for each nesting level
    using IterPair = std::pair<std::vector<NestedInteger>::iterator, std::vector<NestedInteger>::iterator>;
    std::stack<IterPair> s;

public:
    NestedIterator(std::vector<NestedInteger> &nestedList) {
        s.push({nestedList.begin(), nestedList.end()});
    }
    
    int next() {
        // hasNext() guarantees that the top iterator points directly to an integer
        int val = s.top().first->getInteger(); // Fixed: changed getInt() to getInteger()
        s.top().first++; 
        return val;
    }
    
    bool hasNext() {
        while (!s.empty()) {
            auto& curr = s.top();
            
            // If the current list iteration is finished, pop the layer
            if (curr.first == curr.second) {
                s.pop();
                if (!s.empty()) {
                    s.top().first++; // Advance parent list's iterator
                }
                continue;
            }
            
            // If the current element is an integer, it is ready to be fetched
            if (curr.first->isInteger()) {
                return true;
            }
            
            // If it's a nested list, unpack it onto the stack without advancing the current layer yet
            auto& nestedList = curr.first->getList();
            s.push({nestedList.begin(), nestedList.end()});
        }
        return false;
    }
};
