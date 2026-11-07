/*
 * Approach: Hash map from file content to full paths. Split each directory
 * string on spaces; the first token is the directory and each later token is
 * "name(content)". Group paths by content and keep groups of size >= 2.
 * Time: O(L) over the total input length, Space: O(L)
 */
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> byContent;
        for (const string& entry : paths) {
            istringstream in(entry);
            string dir, file;
            in >> dir;
            while (in >> file) {
                size_t open = file.find('(');
                string name = file.substr(0, open);
                string content = file.substr(open + 1, file.size() - open - 2);
                byContent[content].push_back(dir + "/" + name);
            }
        }
        vector<vector<string>> result;
        for (auto& [content, files] : byContent)
            if (files.size() > 1) result.push_back(move(files));
        return result;
    }
};
