// cache_sim: replay a trace of keys through an LRU cache and report the hit rate.
//
//   ./build/cache_sim 3 < trace.txt
//   echo "a b c a d a b" | ./build/cache_sim 2
//
// Keys are whitespace-separated words. Each key is looked up; on a miss it is
// inserted. Capacities may be listed to compare several sizes in one run.

#include "lru_cache.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " CAPACITY [CAPACITY...] < trace\n";
        return 2;
    }
    std::vector<std::size_t> capacities;
    for (int i = 1; i < argc; ++i) {
        char* end = nullptr;
        long v = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || v <= 0) {
            std::cerr << "invalid capacity: " << argv[i] << "\n";
            return 2;
        }
        capacities.push_back(static_cast<std::size_t>(v));
    }

    std::vector<std::string> trace;
    for (std::string key; std::cin >> key;) trace.push_back(key);

    std::cout << "requests: " << trace.size() << "\n";
    std::cout << std::fixed << std::setprecision(1);
    for (std::size_t cap : capacities) {
        lru::LRUCache<std::string, bool> cache(cap);
        for (const auto& key : trace) {
            if (!cache.get(key)) cache.put(key, true);
        }
        const lru::Stats& s = cache.stats();
        std::cout << "capacity " << cap << ": " << s.hits << " hits, " << s.misses
                  << " misses, " << s.evictions << " evictions, hit rate "
                  << s.hitRate() * 100.0 << "%\n";
    }
    return 0;
}
