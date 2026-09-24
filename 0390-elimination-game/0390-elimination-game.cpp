class Solution {
public:
    int lastRemaining(int n) {
        int head = 1;
        int step = 1;
        int remaining = n;
        bool leftToRight = true;
        
        while (remaining > 1) {
            // The head always moves forward if we move Left to Right,
            // OR if we move Right to Left and the count of remaining numbers is odd.
            if (leftToRight || remaining % 2 == 1) {
                head += step;
            }
            
            // In each elimination round, the distance between numbers doubles
            step *= 2;
            // The total count of numbers is cut in half
            remaining /= 2;
            // Alternate the elimination direction
            leftToRight = !leftToRight;
        }
        
        return head;
    }
};
