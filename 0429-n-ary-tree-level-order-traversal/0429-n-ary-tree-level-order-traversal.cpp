/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
    }
};
*/

#include <vector>
#include <queue>

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(Node* root) {
        std::vector<std::vector<int>> result;
        
        // Edge case: if the tree is empty
        if (root == nullptr) {
            return result;
        }
        
        std::queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size(); // Number of nodes at the current level
            std::vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = q.front();
                q.pop();
                
                currentLevel.push_back(currentNode->val);
                
                // Push all children of the current node into the queue
                for (Node* child : currentNode->children) {
                    if (child != nullptr) {
                        q.push(child);
                    }
                }
            }
            
            // Add the completed level to the final result
            result.push_back(currentLevel);
        }
        
        return result;
    }
};
