#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class AllOne {
private:
    // Struct representing a bucket of keys with the same frequency
    struct Bucket {
        int count;
        unordered_set<string> keys;
        Bucket(int c) : count(c) {}
    };

    list<Bucket> buckets; // Doubly linked list of sorted frequency buckets
    unordered_map<string, list<Bucket>::iterator> keyToBucket; // Quick lookups

public:
    AllOne() {}
    
    void inc(string key) {
        // Case 1: Key does not exist yet
        if (keyToBucket.find(key) == keyToBucket.end()) {
            // Check if a bucket with frequency 1 already exists at the front
            if (buckets.empty() || buckets.front().count != 1) {
                buckets.push_front(Bucket(1));
            }
            buckets.front().keys.insert(key);
            keyToBucket[key] = buckets.begin();
        } 
        // Case 2: Key already exists
        else {
            auto currBucket = keyToBucket[key];
            auto nextBucket = next(currBucket);
            
            // Create a new bucket with frequency count + 1 if it doesn't exist
            if (nextBucket == buckets.end() || nextBucket->count != currBucket->count + 1) {
                nextBucket = buckets.insert(nextBucket, Bucket(currBucket->count + 1));
            }
            
            // Move key to the next higher bucket
            nextBucket->keys.insert(key);
            keyToBucket[key] = nextBucket;
            
            // Clean up old bucket
            currBucket->keys.erase(key);
            if (currBucket->keys.empty()) {
                buckets.erase(currBucket);
            }
        }
    }
    
    void dec(string key) {
        // Element is guaranteed to exist per problem constraints
        auto currBucket = keyToBucket[key];
        
        // Case 1: Count becomes 0 (Remove completely)
        if (currBucket->count == 1) {
            keyToBucket.erase(key);
        } 
        // Case 2: Count decreases but stays > 0
        else {
            auto prevBucket = prev(currBucket);
            
            // Create a new bucket with frequency count - 1 if it doesn't exist
            if (currBucket == buckets.begin() || prevBucket->count != currBucket->count - 1) {
                prevBucket = buckets.insert(currBucket, Bucket(currBucket->count - 1));
            }
            
            prevBucket->keys.insert(key);
            keyToBucket[key] = prevBucket;
        }
        
        // Clean up old bucket
        currBucket->keys.erase(key);
        if (currBucket->keys.empty()) {
            buckets.erase(currBucket);
        }
    }
    
    string getMaxKey() {
        if (buckets.empty()) return "";
        return *(buckets.back().keys.begin()); // Returns any key from the highest-count bucket
    }
    
    string getMinKey() {
        if (buckets.empty()) return "";
        return *(buckets.front().keys.begin()); // Returns any key from the lowest-count bucket
    }
};
