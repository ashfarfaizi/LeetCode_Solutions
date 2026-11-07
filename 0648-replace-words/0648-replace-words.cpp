/*
 * Approach: Trie of roots. Insert every dictionary root, then for each word
 * walk the trie and stop at the first node that ends a root; that prefix is
 * the shortest root. If no root matches, keep the word as is.
 * Time: O(D + S) over dictionary and sentence length, Space: O(D * 26)
 */
class Solution {
    struct Node {
        array<int, 26> next{};
        bool end = false;
    };
    vector<Node> trie{1};

public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        for (const string& root : dictionary) {
            int cur = 0;
            for (char ch : root) {
                int c = ch - 'a';
                if (!trie[cur].next[c]) {
                    trie[cur].next[c] = trie.size();
                    trie.emplace_back();
                }
                cur = trie[cur].next[c];
            }
            trie[cur].end = true;
        }
        istringstream in(sentence);
        string word, result;
        while (in >> word) {
            if (!result.empty()) result += ' ';
            int cur = 0;
            size_t len = 0;
            bool found = false;
            for (char ch : word) {
                cur = trie[cur].next[ch - 'a'];
                if (!cur) break;
                ++len;
                if (trie[cur].end) {
                    found = true;
                    break;
                }
            }
            result += found ? word.substr(0, len) : word;
        }
        return result;
    }
};
