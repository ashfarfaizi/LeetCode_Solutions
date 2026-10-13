#include <vector>
#include <set>

class Solution {
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<double> medians;
        std::multiset<int> left_set, right_set;

        // Helper function to balance the sizes of the two multisets
        auto balance = [&]() {
            if (left_set.size() > right_set.size() + 1) {
                right_set.insert(*left_set.rbegin());
                left_set.erase(std::prev(left_set.end()));
            } else if (left_set.size() < right_set.size()) {
                left_set.insert(*right_set.begin());
                right_set.erase(right_set.begin());
            }
        };

        // Helper function to insert a number into the heaps
        auto addNumber = [&](int num) {
            if (left_set.empty() || num <= *left_set.rbegin()) {
                left_set.insert(num);
            } else {
                right_set.insert(num);
            }
            balance();
        };

        // Helper function to remove a number from the heaps
        auto removeNumber = [&](int num) {
            auto it = left_set.find(num);
            if (it != left_set.end()) {
                left_set.erase(it);
            } else {
                right_set.erase(right_set.find(num));
            }
            balance();
        };

        // Helper function to extract the current median
        auto getMedian = [&]() -> double {
            if (k % 2 != 0) {
                return *left_set.rbegin();
            } else {
                return ((double)*left_set.rbegin() + *right_set.begin()) / 2.0;
            }
        };

        // Initialize the first window
        for (int i = 0; i < k; ++i) {
            addNumber(nums[i]);
        }
        medians.push_back(getMedian());

        // Slide the window across the rest of the array
        for (int i = k; i < nums.size(); ++i) {
            removeNumber(nums[i - k]); // Remove the element leaving the window
            addNumber(nums[i]);       // Add the new element entering the window
            medians.push_back(getMedian());
        }

        return medians;
    }
};
