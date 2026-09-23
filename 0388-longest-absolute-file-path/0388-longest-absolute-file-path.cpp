class Solution {
public:
    int lengthLongestPath(string input) {
        // pathLength[i] will store the cumulative path length up to depth level i
        // Since input length <= 10^4, depth level cannot exceed the maximum length boundary
        unordered_map<int, int> pathLength;
        pathLength[0] = 0; // Baseline depth 0 starts with length 0
        
        int maxLength = 0;
        int i = 0;
        int n = input.length();
        
        while (i < n) {
            // Step 1: Find the depth level by counting tabs '\t'
            int level = 0;
            while (i < n && input[i] == '\t') {
                level++;
                i++;
            }
            
            // Step 2: Find the length of the file or directory name
            int nameLength = 0;
            bool isFile = false;
            while (i < n && input[i] != '\n') {
                if (input[i] == '.') {
                    isFile = true;
                }
                nameLength++;
                i++;
            }
            
            // Step 3: Update path tracker or calculate global max file length
            if (isFile) {
                // Total length = parent directory string length + current file string length
                // level variable indicates the count of separator '/' inserted into the path string
                int currentLength = pathLength[level] + nameLength + level;
                maxLength = max(maxLength, currentLength);
            } else {
                // Store the raw string name character count for the children beneath it
                pathLength[level + 1] = pathLength[level] + nameLength;
            }
            
            // Skip the newline character to advance to the next line
            i++;
        }
        
        return maxLength;
    }
};
