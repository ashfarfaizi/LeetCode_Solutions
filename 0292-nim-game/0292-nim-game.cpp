class Solution {
public:
    bool canWinNim(int n) {
        // You lose if n is a multiple of 4, otherwise you win
        return n % 4 != 0;
    }
};
