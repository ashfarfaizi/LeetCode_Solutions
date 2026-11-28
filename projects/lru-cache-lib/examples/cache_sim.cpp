// cache_sim: replay a trace of keys through a cache and report the hit rate.
//
//   ./build/cache_sim 3 < trace.txt
//   echo "a b c a d a b" | ./build/cache_sim 2
//   ./build/cache_sim --policy=both 2 4 < trace.txt
//
// --policy=lru (default), lfu, or both (prints one line per policy).
//
// Keys are whitespace-separated words. Each key is looked up; on a miss it is
// inserted. Capacities may be listed to compare several sizes in one run.

#include "lfu_cache.hpp"
#include "lru_cache.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

template <typename Cache>
static lru::Stats replay(std::size_t cap, const std::vector<std::string>& trace) {
    Cache cache(cap);
    for (const auto& key : trace) {
        if (!cache.get(key)) cache.put(key, true);
    }
    return cache.stats();
}

static void report(const char* label, std::size_t cap, const lru::Stats& s) {
    std::cout << label << "capacity " << cap << ": " << s.hits << " hits, " << s.misses
              << " misses, " << s.evictions << " evictions, hit rate "
              << s.hitRate() * 100.0 << "%\n";
}

int main(int argc, char** argv) {
    const char* usage = " [--policy=lru|lfu|both] CAPACITY [CAPACITY...] < trace\n";
    bool runLru = true, runLfu = false;
    std::vector<std::size_t> capacities;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--policy=", 0) == 0) {
            std::string p = arg.substr(9);
            if (p == "lru") { runLru = true; runLfu = false; }
            else if (p == "lfu") { runLru = false; runLfu = true; }
            else if (p == "both") { runLru = runLfu = true; }
            else {
                std::cerr << "unknown policy: " << p << "\n";
                return 2;
            }
            continue;
        }
        char* end = nullptr;
        long v = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || v <= 0) {
            std::cerr << "invalid capacity: " << argv[i] << "\n";
            return 2;
        }
        capacities.push_back(static_cast<std::size_t>(v));
    }
    if (capacities.empty()) {
        std::cerr << "usage: " << argv[0] << usage;
        return 2;
    }

    std::vector<std::string> trace;
    for (std::string key; std::cin >> key;) trace.push_back(key);

    std::cout << "requests: " << trace.size() << "\n";
    std::cout << std::fixed << std::setprecision(1);
    const bool both = runLru && runLfu;
    for (std::size_t cap : capacities) {
        if (runLru)
            report(both ? "lru " : "", cap, replay<lru::LRUCache<std::string, bool>>(cap, trace));
        if (runLfu)
            report(both ? "lfu " : "", cap, replay<lru::LFUCache<std::string, bool>>(cap, trace));
    }
    return 0;
}
