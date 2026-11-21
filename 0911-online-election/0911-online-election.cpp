/*
 * Approach: precompute the leader after every vote. Walk the votes in time
 * order keeping a count per person; whenever the new voter's count reaches
 * or beats the current leader's, they become the leader (ties go to the most
 * recent vote). A query at time t binary-searches the last vote with
 * time <= t and returns the leader recorded for it.
 *
 * Time:  O(n) construction, O(log n) per query
 * Space: O(n)
 */
class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) : times_(times) {
        unordered_map<int, int> count;
        int leader = -1;
        for (int p : persons) {
            if (++count[p] >= (leader == -1 ? 0 : count[leader])) leader = p;
            leaders_.push_back(leader);
        }
    }

    int q(int t) {
        int idx = int(upper_bound(times_.begin(), times_.end(), t) - times_.begin()) - 1;
        return leaders_[idx];
    }

private:
    vector<int> times_;
    vector<int> leaders_;
};
