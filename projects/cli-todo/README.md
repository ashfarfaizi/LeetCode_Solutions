# cli-todo

`todo`, a small command-line task list written in C++17 with no
dependencies beyond the standard library. Tasks live in a plain text file
that is easy to read, diff and keep in version control.

```
todo [-f FILE] add [-p LEVEL] TEXT...  # add a task, prints its id
todo [-f FILE] list [--pending | --done]  # show tasks, highest priority first
todo [-f FILE] done ID       # mark a task as done
todo [-f FILE] undo ID       # mark a done task as pending again
todo [-f FILE] rm ID         # delete a task
todo [-f FILE] edit ID TEXT  # replace a task's text
todo [-f FILE] pri ID LEVEL  # change a task's priority
todo [-f FILE] clear         # delete all completed tasks
```

`list --pending` shows only unfinished tasks and `list --done` only
finished ones. `clear` prints how many tasks it removed; ids of cleared
tasks are not reused.

`LEVEL` is `high`, `normal` (the default) or `low`, or just `h`, `n`, `l`.
`list` shows high-priority tasks first, then normal, then low; within a
level tasks keep the order they were added.

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
$ todo edit 2 call mum back
$ todo rm 1
$ todo add -p high pay rent
added 3
$ todo list
[ ] 3  (high) pay rent
[ ] 2  call mum back
```

Exit status is `0` on success, `1` for an unknown task id or an unreadable
or malformed file, and `2` for a usage error.

## File format

```
# cli-todo v2
1	1	N	buy milk
2	0	H	pay rent
```

A header line, then one `id<TAB>done<TAB>priority<TAB>text` line per task,
with priority `L`, `N` or `H`. Older `# cli-todo v1` files (no priority
column) still load, with every task at normal priority, and are rewritten
as v2 on the next change. Ids are
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
