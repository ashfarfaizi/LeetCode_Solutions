#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Twitter {
private:
    // Global counter to track order of tweets chronologically
    int timestamp;
    
    // Maps a userId to the list of their tweets: pair<timestamp, tweetId>
    std::unordered_map<int, std::vector<std::pair<int, int>>> userTweets;
    
    // Maps a userId to the set of users they are following
    std::unordered_map<int, std::unordered_set<int>> following;

public:
    Twitter() {
        timestamp = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        // Record the tweet with the current global timestamp
        userTweets[userId].push_back({timestamp++, tweetId});
    }
    
    std::vector<int> getNewsFeed(int userId) {
        // Max-heap stores pairs of: {timestamp, tweetId}
        // It automatically sorts elements so the most recent tweet is at the top
        std::priority_queue<std::pair<int, int>> maxHeap;
        
        // 1. Add the user's own tweets to the heap
        if (userTweets.find(userId) != userTweets.end()) {
            const auto& tweets = userTweets[userId];
            // We only need at most the last 10 tweets from this user
            int count = 0;
            for (auto it = tweets.rbegin(); it != tweets.rend() && count < 10; ++it, ++count) {
                maxHeap.push(*it);
            }
        }
        
        // 2. Add tweets from all the users they follow
        if (following.find(userId) != following.end()) {
            for (int followeeId : following[userId]) {
                if (userTweets.find(followeeId) != userTweets.end()) {
                    const auto& tweets = userTweets[followeeId];
                    int count = 0;
                    for (auto it = tweets.rbegin(); it != tweets.rend() && count < 10; ++it, ++count) {
                        maxHeap.push(*it);
                    }
                }
            }
        }
        
        // 3. Extract up to 10 of the most recent tweets from the heap
        std::vector<int> newsFeed;
        while (!maxHeap.empty() && newsFeed.size() < 10) {
            newsFeed.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        
        return newsFeed;
    }
    
    void follow(int followerId, int followeeId) {
        // A user cannot follow themselves
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        if (following.find(followerId) != following.end()) {
            following[followerId].erase(followeeId);
        }
    }
};
