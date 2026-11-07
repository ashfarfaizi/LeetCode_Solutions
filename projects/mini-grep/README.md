# mini-grep

`mgrep`, a small `grep`-like line filter written in C++17 with no
dependencies beyond the standard library.

```
mgrep [-icn] PATTERN [FILE...]
```

It prints every line that contains `PATTERN` as a plain substring. With no
`FILE` (or `-`) it reads standard input; with several files each line is
prefixed with `name:`.

| option | effect                     |
|--------|----------------------------|
| `-i`   | ignore case (ASCII)        |
| `-n`   | prefix lines with `N:`     |
| `-c`   | print only a match count   |

Exit status is `0` if any line matched, `1` if none did and `2` on a usage
error or a file that cannot be opened. Short options can be combined and
`--` ends option parsing.

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

With `-c` each file prints one count line (including `0`).

## Layout

```
src/grep.hpp, src/grep.cpp   Matcher and scan(): the testable core
src/main.cpp                 command-line parsing and file handling
tests/tests.cpp              minimal self-contained test runner
```
