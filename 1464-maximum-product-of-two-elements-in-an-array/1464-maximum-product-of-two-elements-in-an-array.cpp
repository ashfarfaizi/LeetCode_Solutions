class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int largest = 0;
        int secondLargest = 0;

        for (int x : nums) {
            if (x > largest) {
                secondLargest = largest;
                largest = x;
            } 
            else if (x > secondLargest) {
                secondLargest = x;
            }
        }

        return (largest - 1) * (secondLargest - 1);
    }
};