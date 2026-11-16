# cli-todo

`todo`, a small command-line task list written in C++17 with no
dependencies beyond the standard library. Tasks live in a plain text file
that is easy to read, diff and keep in version control.

```
todo [-f FILE] add TEXT...   # add a task, prints its id
todo [-f FILE] list          # show all tasks
todo [-f FILE] done ID       # mark a task as done
```

The list is read from `-f FILE`, else `$TODO_FILE`, else `./todo.txt`. A
missing file is treated as an empty list and created on the first change.

```
$ todo add buy milk
added 1
$ todo add call mum
added 2
$ todo done 1
$ todo list
[x] 1  buy milk
[ ] 2  call mum
```

Exit status is `0` on success, `1` for an unknown task id or an unreadable
or malformed file, and `2` for a usage error.

## File format

```
# cli-todo v1
1	1	buy milk
2	0	call mum
```

A header line, then one `id<TAB>done<TAB>text` line per task. Ids are
never reused, even after loading a file. Lines starting with `#` and blank
lines are ignored.

## Build and test

```
make          # builds build/todo and runs all tests
make test     # unit tests (tests/tests.cpp) + CLI smoke tests (tests/cli.sh)
make clean
```

Or without make:

```
g++ -std=c++17 -Wall -Wextra -O2 -Isrc src/*.cpp -o todo
```

## Layout

- `src/todo.hpp`, `src/todo.cpp` — `TodoList` model, load/save
- `src/main.cpp` — command-line interface
- `tests/` — unit tests and CLI smoke tests
