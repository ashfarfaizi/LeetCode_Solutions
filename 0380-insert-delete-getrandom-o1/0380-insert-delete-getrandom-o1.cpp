#include <vector>
#include <unordered_map>
#include <cstdlib>

class RandomizedSet {
private:
    std::vector<int> nums;                  // Stores the actual elements
    std::unordered_map<int, int> valToIndex; // Maps value -> its index in the nums vector

public:
    RandomizedSet() {
        // Initialization handled implicitly
    }
    
    bool insert(int val) {
        // If the value already exists, return false
        if (valToIndex.find(val) != valToIndex.end()) {
            return false;
        }
        
        // Add element to the end of the list and log its index
        valToIndex[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        // If the value does not exist, return false
        if (valToIndex.find(val) == valToIndex.end()) {
            return false;
        }
        
        // Get the index of the element to delete and the value of the last element
        int targetIdx = valToIndex[val];
        int lastVal = nums.back();
        
        // Move the last element into the place of the element we want to delete
        nums[targetIdx] = lastVal;
        valToIndex[lastVal] = targetIdx;
        
        // Remove the last element from both structures
        nums.pop_back();
        valToIndex.erase(val);
        return true;
    }
    
    int getRandom() {
        // Pick a random index uniformly
        int randomIdx = std::rand() % nums.size();
        return nums[randomIdx];
    }
};
