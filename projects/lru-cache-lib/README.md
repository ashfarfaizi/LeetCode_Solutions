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
| `size()`, `empty()`, `capacity()` | the obvious                       |

`stats()` returns hit, miss and eviction counters plus `hitRate()`;
only `get` counts towards hits and misses. `resetStats()` zeroes them.

No dependencies beyond the standard library.

## Build & test

```sh
make test     # builds build/tests and runs it
make clean
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o tests_bin && ./tests_bin
```

## Layout

```
include/lru_cache.hpp   the cache (header-only)
tests/tests.cpp         minimal self-contained test runner
```
