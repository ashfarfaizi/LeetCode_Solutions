#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Transfer elements to a hash set for O(1) lookups
        unordered_set<string> wordDictionary(wordList.begin(), wordList.end());
        
        // If the endWord isn't in the list, no valid path can ever be constructed
        if (!wordDictionary.count(endWord)) {
            return 0;
        }

        // Two frontiers for the bidirectional search
        unordered_set<string> forwardFrontier;
        unordered_set<string> backwardFrontier;

        forwardFrontier.insert(beginWord);
        backwardFrontier.insert(endWord);

        // Keep track of the number of words in the transformation sequence
        int transformationSteps = 1;

        while (!forwardFrontier.empty() && !backwardFrontier.empty()) {
            // Optimization trick: Always search from the smaller frontier to minimize variations
            if (forwardFrontier.size() > backwardFrontier.size()) {
                swap(forwardFrontier, backwardFrontier);
            }

            unordered_set<string> nextLayerFrontier;

            // Iterate over every word in our active search layer
            for (string word : forwardFrontier) {
                // Mutate each character slot systematically
                for (size_t i = 0; i < word.length(); ++i) {
                    char originalChar = word[i];

                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        word[i] = ch;

                        // Intersection check: If this mutation exists in the opposite set, paths met!
                        if (backwardFrontier.count(word)) {
                            return transformationSteps + 1;
                        }

                        // If it's a valid next word in the dictionary, add to next layer
                        if (wordDictionary.count(word)) {
                            nextLayerFrontier.insert(word);
                            wordDictionary.erase(word); // Remove to prevent cycle re-traversal
                        }
                    }
                    word[i] = originalChar; // Reset character change before moving to next slot
                }
            }

            // Move forward to the next layer row tier and increment steps
            forwardFrontier = move(nextLayerFrontier);
            transformationSteps++;
        }

        return 0; // Fronts exhausted without ever meeting means no sequence exists
    }
};
