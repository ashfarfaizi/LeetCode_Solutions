# mini-grep

`mgrep`, a small `grep`-like line filter written in C++17 with no
dependencies beyond the standard library.

```
mgrep [-icnovwxlLqHh] [-m NUM] [-A NUM] PATTERN [FILE...]
```

It prints every line that contains `PATTERN` as a plain substring. With no
`FILE` (or `-`) it reads standard input; with several files each line is
prefixed with `name:`. `-H` adds that prefix even for a single file and `-h`
leaves it off even for several; whichever comes last wins.

| option | effect                     |
|--------|----------------------------|
| `-i`   | ignore case (ASCII)        |
| `-n`   | prefix lines with `N:`     |
| `-c`   | print only a match count   |
| `-o`   | print only matched text    |
| `-v`   | select non-matching lines  |
| `-w`   | match whole words only     |
| `-x`   | match whole lines only     |
| `-m N` | stop after `N` matches     |
| `-A N` | `N` lines of context after |
| `-l`   | list files that match      |
| `-L`   | list files that don't      |
| `-q`   | quiet: exit status only    |

Exit status is `0` if any line matched, `1` if none did and `2` on a usage
error or a file that cannot be opened. With `-q` nothing is printed, reading
stops at the first selected line, and a match gives `0` even if an earlier
file could not be opened, so it slots straight into shell conditions:
`if mgrep -q TODO notes.md; then ...`.

Short options can be combined and `--` ends option parsing.

## Build & test

```sh
make           # builds build/mgrep and runs the tests
make test      # builds build/tests and runs it
make clean
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc tests/tests.cpp src/grep.cpp -o tests_bin && ./tests_bin
```

## Usage

```sh
$ printf 'Error: disk\nok\nerror: net\n' | ./build/mgrep -i error
Error: disk
error: net
$ ./build/mgrep -n namespace src/grep.hpp
8:namespace mgrep {
38:}  // namespace mgrep
$ printf 'a\nb\na\n' | ./build/mgrep -c a
2
```

A word character is a letter, digit or `_`, so `-w cat` matches `the cat`
and `(cat)` but not `cats` or `cat_food`. `-v` combines with the others,
e.g. `mgrep -vc '#' config` counts lines that are not comments. `-x`
overrides `-w`, and `mgrep -vx '' file` drops blank lines.

With `-c` each file prints one count line (including `0`). `-m N` applies
per file and stops reading as soon as `N` lines have matched, so
`mgrep -m1 TODO big.log` returns quickly; with `-c` it caps the count. The
value may be attached (`-m3`) or separate (`-m 3`).

`-o` prints every non-overlapping match on its own line (keeping the
`name:` and `N:` prefixes), which is handy for pulling tokens out of logs:
`mgrep -oiw error app.log | wc -l` counts occurrences rather than lines.
With `-v` it prints nothing, and `-c` still counts lines.

`-A N` prints up to `N` lines after each match. Context lines use `-`
instead of `:` after the file name and line number (`app.log-12-...`), and
groups that are not next to each other are separated by a `--` line, so
`mgrep -n -A2 panic app.log` shows each panic with the two lines that
followed it. With `-m` the trailing context of the last match is still
printed. Context is ignored with `-c` and `-o`.

`-l` prints each file name once, as soon as a selected line is found, and
`-L` prints the files where none was. For example `mgrep -L '#pragma once'
src/*.hpp` finds headers missing a guard. With `-l` or `-L` the exit status
is `0` when at least one name was printed.

## Layout

```
src/grep.hpp, src/grep.cpp   Matcher and scan(): the testable core
src/main.cpp                 command-line parsing and file handling
tests/tests.cpp              minimal self-contained test runner
```
