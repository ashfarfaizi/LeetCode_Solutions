#include <vector>
#include <random>

class Solution {
private:
    double r, x, y;
    std::mt19937 gen;
    std::uniform_real_distribution<double> disX;
    std::uniform_real_distribution<double> disY;

public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        x = x_center;
        y = y_center;
        
        // Initialize random number generator
        std::random_device rd;
        gen = std::mt19937(rd());
        
        // Bounding square coordinates
        disX = std::uniform_real_distribution<double>(x - r, x + r);
        disY = std::uniform_real_distribution<double>(y - r, y + r);
    }
    
    std::vector<double> randPoint() {
        while (true) {
            double randX = disX(gen);
            double randY = disY(gen);
            
            // Check if the point lies within the circle radius
            if ((randX - x) * (randX - x) + (randY - y) * (randY - y) <= r * r) {
                return {randX, randY};
            }
        }
    }
};
