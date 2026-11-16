/*
 * Approach: Rooms and keys form a directed graph. Run an iterative DFS from
 * room 0, following keys to unvisited rooms, and check that every room was
 * reached.
 * Time: O(n + total keys), Space: O(n)
 */
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size(), visited = 1;
        vector<bool> seen(n, false);
        seen[0] = true;
        vector<int> stack = {0};
        while (!stack.empty()) {
            int room = stack.back();
            stack.pop_back();
            for (int key : rooms[room])
                if (!seen[key]) {
                    seen[key] = true;
                    ++visited;
                    stack.push_back(key);
                }
        }
        return visited == n;
    }
};
