#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Map departure airports to a min-heap of destinations
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        
        for (const auto& ticket : tickets) {
            graph[ticket[0]].push(ticket[1]);
        }
        
        vector<string> itinerary;
        dfs("JFK", graph, itinerary);
        
        // The path is constructed backwards, so reverse it
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }

private:
    void dfs(const string& airport, 
             unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& graph, 
             vector<string>& itinerary) {
        
        // Destructively visit targets in lexicographical order
        while (!graph[airport].empty()) {
            string next = graph[airport].top();
            graph[airport].pop(); // Use the ticket (remove edge)
            dfs(next, graph, itinerary);
        }
        
        // Push to itinerary when no more outgoing flights are left
        itinerary.push_back(airport);
    }
};
