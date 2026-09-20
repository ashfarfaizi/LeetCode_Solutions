#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

class RandomizedCollection {
private:
    std::vector<int> nums;
    std::unordered_map<int, std::unordered_set<int>> valToIndices;

public:
    RandomizedCollection() {
        // Handled implicitly
    }
    
    bool insert(int val) {
        bool notPresent = valToIndices[val].empty();
        valToIndices[val].insert(nums.size());
        nums.push_back(val);
        return notPresent;
    }
    
    bool remove(int val) {
        if (valToIndices[val].empty()) {
            return false;
        }
        
        int removeIdx = *valToIndices[val].begin();
        int lastVal = nums.back();
        int lastIdx = nums.size() - 1;
        
        // Move the last element to the target slot
        nums[removeIdx] = lastVal;
        
        // FIX: Erase old indices before inserting new ones
        valToIndices[val].erase(removeIdx);
        valToIndices[lastVal].erase(lastIdx);
        
        // Only insert if the index belongs to a valid remaining index slot
        if (removeIdx != lastIdx) {
            valToIndices[lastVal].insert(removeIdx);
        }
        
        nums.pop_back();
        return true;
    }
    
    int getRandom() {
        return nums[std::rand() % nums.size()];
    }
};
