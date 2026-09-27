#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    // Helper function to perform DFS and find the cumulative product path
    double dfs(const string& src, const string& dst, unordered_set<string>& visited,
               unordered_map<string, unordered_map<string, double>>& adj) {
        // If source node matches target, we found the path
        if (src == dst) return 1.0;
        
        visited.insert(src);
        
        for (auto& neighbor : adj[src]) {
            string nextNode = neighbor.first;
            double edgeWeight = neighbor.second;
            
            if (visited.find(nextNode) == visited.end()) {
                double pathResult = dfs(nextNode, dst, visited, adj);
                if (pathResult != -1.0) {
                    return edgeWeight * pathResult;
                }
            }
        }
        
        return -1.0;
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // Graph represented as an adjacency list: adj[U][V] = weight
        unordered_map<string, unordered_map<string, double>> adj;
        
        // Step 1: Build the graph
        for (int i = 0; i < equations.size(); ++i) {
            string u = equations[i][0];
            string v = equations[i][1];
            double val = values[i];
            
            adj[u][v] = val;
            adj[v][u] = 1.0 / val;
        }
        
        vector<double> results;
        
        // Step 2: Evaluate each query
        for (const auto& q : queries) {
            string src = q[0];
            string dst = q[1];
            
            // If either variable doesn't exist in our graph, it is undefined
            if (adj.find(src) == adj.end() || adj.find(dst) == adj.end()) {
                results.push_back(-1.0);
            } else {
                unordered_set<string> visited;
                double ans = dfs(src, dst, visited, adj);
                results.push_back(ans);
            }
        }
        
        return results;
    }
};
