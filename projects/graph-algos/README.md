# graph-algos

A small header-only C++17 library of classic graph algorithms, written to be
easy to read and easy to drop into a contest or side project.

## Features

- `ga::Graph` — weighted adjacency-list graph (directed or undirected)
- `bfs_order`, `bfs_distances`, `dfs_order` traversals
- `connected_components` labelling
- `dijkstra` single-source shortest paths with `path_to` reconstruction
  (`shortest_paths.hpp`)
- `bellman_ford` for negative weights, with negative-cycle detection

## Build and test

```sh
make test          # builds build/tests with -Wall -Wextra and runs it
```

or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o build/tests && ./build/tests
```

## Usage

```cpp
#include "graph.hpp"

ga::Graph g(4);
g.add_edge(0, 1);
g.add_edge(1, 2);
auto dist = ga::bfs_distances(g, 0);  // {0, 1, 2, -1}
```
