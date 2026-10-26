#include <string>
#include <unordered_map>
#include <random>

class Solution {
private:
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const std::string baseUrl = "http://tinyurl.com/";
    
    std::unordered_map<std::string, std::string> codeToUrl; // Map to look up original URL
    std::unordered_map<std::string, std::string> urlToCode; // Map to handle duplicate long URLs
    
    std::mt19937 gen; // Reliable pseudo-random number generator

    // Helper function to generate a random 6-character key
    std::string generateRandomKey() {
        std::string key = "";
        std::uniform_int_distribution<int> dist(0, alphabet.size() - 1);
        for (int i = 0; i < 6; ++i) {
            key += alphabet[dist(gen)];
        }
        return key;
    }

public:
    Solution() {
        // Initialize random device and seed the engine
        std::random_device rd;
        gen.seed(rd());
    }

    // Encodes a URL to a shortened URL.
    std::string encode(std::string longUrl) {
        // If the URL has already been shortened, return the existing code
        if (urlToCode.count(longUrl)) {
            return baseUrl + urlToCode[longUrl];
        }
        
        std::string key = generateRandomKey();
        // Keep generating a new key in case of an extremely rare hash collision
        while (codeToUrl.count(key)) {
            key = generateRandomKey();
        }
        
        // Save the bidirectional mapping mappings
        codeToUrl[key] = longUrl;
        urlToCode[longUrl] = key;
        
        return baseUrl + key;
    }

    // Decodes a shortened URL to its original URL.
    std::string decode(std::string shortUrl) {
        // Extract the 6-character key from the end of the short URL string
        std::string key = shortUrl.substr(shortUrl.find_last_of('/') + 1);
        return codeToUrl[key];
    }
};

