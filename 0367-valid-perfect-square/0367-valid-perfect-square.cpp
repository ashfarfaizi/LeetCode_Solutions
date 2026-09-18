class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 1) return false;
        
        long long left = 1;
        long long right = num;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long square = mid * mid;
            
            if (square == num) {
                return true;
            } else if (square > num) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return false;
    }
};
