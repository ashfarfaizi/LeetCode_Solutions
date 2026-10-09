#include <unordered_map>
#include <list>

class LFUCache {
private:
    struct Node {
        int key;
        int value;
        int freq;
    };

    int cap;
    int min_freq;
    
    // Maps key -> iterator pointing to the Node in its frequency list
    std::unordered_map<int, std::list<Node>::iterator> key_to_node;
    
    // Maps frequency -> doubly linked list of Nodes with that frequency
    std::unordered_map<int, std::list<Node>> freq_to_list;

    // Helper function to increase a node's frequency and move it to the correct list
    void updateFrequency(std::list<Node>::iterator it) {
        int key = it->key;
        int value = it->value;
        int freq = it->freq;
        
        // Remove from the current frequency list
        freq_to_list[freq].erase(it);
        
        // If the current list becomes empty and it was the min_freq, increment min_freq
        if (freq_to_list[freq].empty()) {
            freq_to_list.erase(freq);
            if (min_freq == freq) {
                min_freq++;
            }
        }
        
        // Insert into the incremented frequency list (back of the list is most recent)
        int new_freq = freq + 1;
        freq_to_list[new_freq].push_back({key, value, new_freq});
        
        // Update the main hash map with the new iterator position
        key_to_node[key] = std::prev(freq_to_list[new_freq].end());
    }

public:
    LFUCache(int capacity) {
        cap = capacity;
        min_freq = 0;
    }
    
    int get(int key) {
        if (key_to_node.find(key) == key_to_node.end()) {
            return -1;
        }
        
        auto it = key_to_node[key];
        int val = it->value;
        updateFrequency(it);
        return val;
    }
    
    void put(int key, int value) {
        if (cap <= 0) return;
        
        // Case 1: Key already exists -> Update value and update frequency
        if (key_to_node.find(key) != key_to_node.end()) {
            auto it = key_to_node[key];
            it->value = value;
            updateFrequency(it);
            return;
        }
        
        // Case 2: Cache is at capacity -> Evict the LFU (and LRU tie-breaker) element
        if (key_to_node.size() == cap) {
            // The front of the min_freq list is the oldest element (LRU tie-breaker)
            auto& min_list = freq_to_list[min_freq];
            int key_to_evict = min_list.front().key;
            
            // Remove from both structures
            min_list.pop_front();
            key_to_node.erase(key_to_evict);
            
            if (min_list.empty()) {
                freq_to_list.erase(min_freq);
            }
        }
        
        // Case 3: Insert the new element
        min_freq = 1; // A brand new element always starts with a frequency of 1
        freq_to_list[min_freq].push_back({key, value, min_freq});
        key_to_node[key] = std::prev(freq_to_list[min_freq].end());
    }
};
