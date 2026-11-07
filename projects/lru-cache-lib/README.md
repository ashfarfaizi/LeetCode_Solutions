# lru-cache-lib

A small header-only C++17 LRU (least recently used) cache.

`lru::LRUCache<Key, Value>` keeps at most `capacity` entries. Reading or
writing a key makes it the most recently used; inserting into a full cache
evicts the least recently used entry. `get` and `put` are O(1) on average
(a `std::list` for recency order plus an `std::unordered_map` index).

```cpp
#include "lru_cache.hpp"

lru::LRUCache<int, std::string> cache(2);
cache.put(1, "one");
cache.put(2, "two");
cache.get(1);            // std::optional -> "one"; 2 is now least recent
cache.put(3, "three");   // evicts 2
cache.get(2);            // std::nullopt
```

Other operations:

| call            | effect                                              |
|-----------------|-----------------------------------------------------|
| `peek(k)`       | like `get` but does not change recency              |
| `contains(k)`   | membership test, does not change recency            |
| `erase(k)`      | removes `k`, returns whether it was present         |
| `clear()`       | removes everything                                  |
| `resize(n)`     | changes capacity; shrinking evicts LRU entries      |
| `keys()`        | keys from most to least recently used               |
| `forEach(fn)`   | visits `(key, value)` pairs in that order           |
| `size()`, `empty()`, `capacity()` | the obvious                       |

`stats()` returns hit, miss and eviction counters plus `hitRate()`;
only `get` counts towards hits and misses. `resetStats()` zeroes them.

To react to capacity evictions (for example to write dirty entries back),
pass a callback to the constructor or `setEvictionCallback`:

```cpp
lru::LRUCache<std::string, Page> pages(64, [](const std::string& key, const Page& p) {
    if (p.dirty) flush(key, p);
});
```

The callback runs after the entry has been removed and is not called for
`erase()` or `clear()`.

For use from several threads, `lru::ConcurrentLRUCache` (in
`concurrent_lru_cache.hpp`) guards a cache with a single mutex and adds
`getOrCompute(key, factory)`:

```cpp
lru::ConcurrentLRUCache<int, Result> results(1024);
Result r = results.getOrCompute(id, [&] { return expensiveLookup(id); });
```

The factory runs outside the lock, so it may run more than once for the same
key under contention.

No dependencies beyond the standard library.

## Build & test

```sh
make          # builds build/cache_sim and runs the tests
make test     # builds build/tests and runs it
make clean
```

## Example: cache simulator

`examples/cache_sim.cpp` replays a whitespace-separated trace of keys and
reports how each capacity would perform:

```sh
$ echo "a b c a d a b e a b" | ./build/cache_sim 2 3
requests: 10
capacity 2: 1 hits, 9 misses, 7 evictions, hit rate 10.0%
capacity 3: 4 hits, 6 misses, 3 evictions, hit rate 40.0%
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o tests_bin -pthread && ./tests_bin
```

## Layout

```
include/lru_cache.hpp              the cache (header-only)
include/concurrent_lru_cache.hpp   mutex-guarded wrapper
examples/cache_sim.cpp             trace-driven hit-rate simulator
tests/tests.cpp                    minimal self-contained test runner
```
