#include <vector>
#include <queue>

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // Step 1: Build adjacency list and calculate indegrees
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> indegree(numCourses, 0);
        
        for (const auto& pre : prerequisites) {
            int course = pre[0];
            int prereq = pre[1];
            adj[prereq].push_back(course); // Directed edge from prereq to course
            indegree[course]++;
        }
        
        // Step 2: Push all courses with 0 prerequisites into a queue
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Step 3: Process the courses
        std::vector<int> order;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);
            
            // Reduce the dependency count for all courses relying on 'curr'
            for (int nextCourse : adj[curr]) {
                indegree[nextCourse]--;
                // If all prerequisites are cleared, add it to the queue
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // Step 4: Check if we successfully included all courses
        if (order.size() == numCourses) {
            return order;
        }
        
        // If order size doesn't match numCourses, a cycle exists
        return {};
    }
};
