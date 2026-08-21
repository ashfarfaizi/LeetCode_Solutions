#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<string>> adjList;
    unordered_map<string, int> minDepth;
    vector<vector<string>> results;
    
    // Backtrack from endWord to beginWord to construct the shortest paths
    void dfs(const string& currentWord, const string& beginWord, vector<string>& path) {
        if (currentWord == beginWord) {
            vector<string> validPath = path;
            reverse(validPath.begin(), validPath.end());
            results.push_back(validPath);
            return;
        }
        
        int currentLevel = minDepth[currentWord];
        for (const string& parent : adjList[currentWord]) {
            // Traverse backward only along paths that conform to the minimum step metric
            if (minDepth.count(parent) && minDepth[parent] == currentLevel - 1) {
                path.push_back(parent);
                dfs(parent, beginWord, path);
                path.pop_back(); // Backtrack step
            }
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return {};
        
        // Setup initial BFS conditions
        queue<string> q;
        q.push(beginWord);
        minDepth[beginWord] = 0;
        
        bool foundShortestPath = false;
        
        while (!q.empty() && !foundShortestPath) {
            int levelSize = q.size();
            unordered_set<string> visitedThisLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                string current = q.front();
                q.pop();
                
                int currDist = minDepth[current];
                string temp = current;
                
                // Generate all valid 1-letter mutation permutations
                for (int j = 0; j < temp.length(); ++j) {
                    char originalChar = temp[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == originalChar) continue;
                        temp[j] = c;
                        
                        if (dict.count(temp)) {
                            // If it's a completely new node or found at the same optimal depth
                            if (!minDepth.count(temp) || minDepth[temp] == currDist + 1) {
                                if (!minDepth.count(temp)) {
                                    minDepth[temp] = currDist + 1;
                                    q.push(temp);
                                }
                                // Map directed edge from destination to origin to ease backward traversal
                                adjList[temp].push_back(current);
                                
                                if (temp == endWord) {
                                    foundShortestPath = true;
                                }
                            }
                        }
                    }
                    temp[j] = originalChar; // Revert transformation
                }
            }
        }
        
        // If a path to endWord exists, build out the sequence listings via DFS
        if (foundShortestPath) {
            vector<string> path = {endWord};
            dfs(endWord, beginWord, path);
        }
        
        return results;
    }
};
