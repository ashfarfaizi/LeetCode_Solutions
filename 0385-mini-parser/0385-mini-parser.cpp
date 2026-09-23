class Solution {
public:
    NestedInteger deserialize(string s) {
        // Case 1: Standalone integer without any nested lists
        if (s.empty()) return NestedInteger();
        if (s[0] != '[') {
            return NestedInteger(stoi(s));
        }
        
        stack<NestedInteger> st;
        int num = 0;
        bool negative = false;
        bool inNum = false; // Tracks if we are currently reading digit characters
        
        for (int i = 0; i < s.length(); ++i) {
            char ch = s[i];
            
            if (ch == '[') {
                // Start of a new sublist -> push an empty container onto the stack
                st.push(NestedInteger());
            } 
            else if (ch == '-') {
                negative = true;
                inNum = true;
            } 
            else if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
                inNum = true;
            } 
            else if (ch == ',' || ch == ']') {
                // Element boundary reached -> Append building number to current active sublist
                if (inNum) {
                    if (negative) num = -num;
                    st.top().add(NestedInteger(num));
                    
                    // Reset number building flags
                    num = 0;
                    negative = false;
                    inNum = false;
                }
                
                // If it's a closing bracket, the current sublist container is fully completed
                if (ch == ']' && st.size() > 1) {
                    NestedInteger finishedSublist = st.top();
                    st.pop();
                    // Append the closed list into its parent list container
                    st.top().add(finishedSublist);
                }
            }
        }
        
        return st.top();
    }
};
