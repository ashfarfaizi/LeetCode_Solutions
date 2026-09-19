class Solution {
private:
    const int MOD = 1337;

    // Helper function to calculate (base^exp) % 1337 using Binary Exponentiation
    int power(int base, int exp) {
        base %= MOD;
        int result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        return result;
    }

public:
    int superPow(int a, vector<int>& b) {
        int result = 1;
        for (int digit : b) {
            // formula: (result^10 * a^digit) % MOD
            result = (power(result, 10) * power(a, digit)) % MOD;
        }
        return result;
    }
};
