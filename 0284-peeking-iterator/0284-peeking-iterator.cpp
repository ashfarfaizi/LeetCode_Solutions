/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
private:
    int next_val;       // Stores the cached next element
    bool has_next_val;  // Flags if the cache has a valid value

    // Helper function to advance the underlying iterator and update the cache
    void advanceCache() {
        if (Iterator::hasNext()) {
            next_val = Iterator::next();
            has_next_val = true;
        } else {
            has_next_val = false;
        }
    }

public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize the cache with the first element of the iterator
	    advanceCache();
	}
	
    // Returns the next element in the array without moving the pointer.
	int peek() {
        return next_val;
	}
	
	// Returns the next element in the array and moves the pointer to the next element.
	int next() {
	    int curr_val = next_val;
        advanceCache(); // Move cache forward for the next operations
	    return curr_val;
	}
	
	// Returns true if there are still elements in the array.
	bool hasNext() const {
	    return has_next_val;
	}
};
