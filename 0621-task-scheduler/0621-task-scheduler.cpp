/*
 * Approach: The most frequent task dictates the layout: maxFreq - 1 full frames
 * of length n + 1, followed by one slot per task that also has maxFreq. If there
 * are enough other tasks to fill every gap, no idling is needed and the answer
 * is just the number of tasks.
 * Time: O(t), Space: O(1) (26 counters)
 */
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26] = {0};
        for (char c : tasks) ++freq[c - 'A'];
        int maxFreq = *max_element(freq, freq + 26);
        int maxCount = count(freq, freq + 26, maxFreq);
        int framed = (maxFreq - 1) * (n + 1) + maxCount;
        return max(framed, static_cast<int>(tasks.size()));
    }
};
