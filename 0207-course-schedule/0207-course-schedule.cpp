#include <vector>
#include <queue>

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // Step 1: Build the adjacency list and indegree array
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> indegree(numCourses, 0);
        
        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prerequisite = pre[1];
            adj[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        // Step 2: Queue all courses that have no prerequisites (indegree == 0)
        std::queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Step 3: Process the queue and keep a count of courses we can take
        int completedCoursesCount = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            completedCoursesCount++;
            
            // For each course that depends on 'curr', decrease its prerequisite count
            for (int neighbor : adj[curr]) {
                indegree[neighbor]--;
                // If all prerequisites are cleared, we can now take this course
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // If we were able to process all courses, there are no cycles
        return completedCoursesCount == numCourses;
    }
};
