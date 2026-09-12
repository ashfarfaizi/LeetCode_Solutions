class Solution {
public:
    bool isValidSerialization(string preorder) {
        stringstream ss(preorder);
        string node;
        int slots = 1; // The root requires 1 slot initially
        
        while (getline(ss, node, ',')) {
            // Processing a node always consumes 1 slot
            slots--;
            
            // If slots drop below zero before finishing, it's an invalid tree
            if (slots < 0) return false;
            
            // A non-empty/non-null node creates 2 new branch slots
            if (node != "#") {
                slots += 2;
            }
        }
        
        // All slots must be perfectly consumed at the end
        return slots == 0;
    }
};
