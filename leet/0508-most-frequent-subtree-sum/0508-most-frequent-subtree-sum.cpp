class Solution {
private:
    unordered_map<int, int> sumCounts;
    int maxCount = 0;

    // Helper function to perform post-order traversal
    int calculateSubtreeSum(TreeNode* root) {
        if (!root) return 0;

        // Recursively compute the left and right subtree sums
        int leftSum = calculateSubtreeSum(root->left);
        int rightSum = calculateSubtreeSum(root->right);

        // Subtree sum including the current node itself
        int currentSum = root->val + leftSum + rightSum;

        // Update the frequency map and track the maximum frequency
        sumCounts[currentSum]++;
        maxCount = max(maxCount, sumCounts[currentSum]);

        return currentSum;
    }

public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        // Step 1: Populate frequencies using DFS
        calculateSubtreeSum(root);

        vector<int> result;
        // Step 2: Collect all sums that have the maximum frequency
        for (const auto& pair : sumCounts) {
            if (pair.second == maxCount) {
                result.push_back(pair.first);
            }
        }

        return result;
    }
};
