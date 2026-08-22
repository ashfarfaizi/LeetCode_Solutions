class Solution {
public:
    // Hash map to store the mapping from original node to cloned node
    unordered_map<Node*, Node*> mp;

    Node* cloneGraph(Node* node) {
        // Base case: if the input graph is empty
        if (node == nullptr) {
            return nullptr;
        }
        
        // If the node has already been cloned, return its existing clone
        if (mp.find(node) != mp.end()) {
            return mp[node];
        }
        
        // Create a copy of the current node (neighbors list starts empty)
        Node* clone = new Node(node->val);
        mp[node] = clone; // Map original node to the clone
        
        // Recursively clone all neighbors and append them to the cloned node's neighbors list
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }
        
        return clone;
    }
};
