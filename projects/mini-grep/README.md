# mini-grep

`mgrep`, a small `grep`-like line filter written in C++17 with no
dependencies beyond the standard library.

```
mgrep [-bicnovwxlLqrsHh] [-m NUM] [-A NUM] [-B NUM] [-C NUM]
      {PATTERN | -e PATTERN... | -f FILE...} [FILE...]
```

It prints every line that contains `PATTERN` as a plain substring. With no
`FILE` (or `-`) it reads standard input; with several files each line is
prefixed with `name:`. `-H` adds that prefix even for a single file and `-h`
leaves it off even for several; whichever comes last wins.

| option | effect                     |
|--------|----------------------------|
| `-e P` | extra pattern (repeatable) |
| `-f F` | patterns from file `F`     |
| `-i`   | ignore case (ASCII)        |
| `-n`   | prefix lines with `N:`     |
| `-b`   | prefix with byte offset    |
| `-c`   | print only a match count   |
| `-o`   | print only matched text    |
| `-v`   | select non-matching lines  |
| `-w`   | match whole words only     |
| `-x`   | match whole lines only     |
| `-m N` | stop after `N` matches     |
| `-A N` | `N` lines of context after |
| `-B N` | `N` lines of context before|
| `-C N` | same as `-A N -B N`        |
| `-l`   | list files that match      |
| `-L`   | list files that don't      |
| `-q`   | quiet: exit status only    |
| `-s`   | no "cannot open" messages  |
| `-r`   | search directories too     |

Exit status is `0` if any line matched, `1` if none did and `2` on a usage
error or a file that cannot be opened. With `-q` nothing is printed, reading
stops at the first selected line, and a match gives `0` even if an earlier
file could not be opened, so it slots straight into shell conditions:
`if mgrep -q TODO notes.md; then ...`.

`-s` suppresses the message for a file that cannot be opened; the other
files are still searched and the exit status is still `2`, so
`mgrep -s TODO *.cpp missing.cpp` prints only matches.

`-r` searches every regular file below each directory argument, in sorted
path order, and searches the current directory when no `FILE` is given; file
names are shown by default, so `mgrep -rn TODO src` reads like a list of
locations. Without `-r` a directory argument is reported (`is a directory`)
and gives exit status `2`.

Short options can be combined and `--` ends option parsing, so
`mgrep -- --help notes.md` searches for the text `--help`. `mgrep --help`
prints a summary of every option to standard output and exits `0`; any other
`--long` option is rejected with status `2`.

## Build & test

```sh
make           # builds build/mgrep and runs the tests
make test      # runs the unit tests and the tests/cli.sh smoke tests
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

`-b` prefixes each output line with the 0-based byte offset of that line in
its input (after the `N:` prefix when `-n` is also given); with `-o` it is the
offset of the match itself, so `mgrep -bo MAGIC blob.txt` tells you exactly
where each occurrence starts.

`-e PATTERN` can be given several times and a line is selected when it
contains any of them: `mgrep -e WARN -e ERROR app.log`. Once `-e` is used
there is no positional pattern, so every remaining argument is a file. It is
also the way to search for text that starts with `-` (`mgrep -e -v`). With
`-o`, where patterns overlap the leftmost match is printed, and the longest
one when several start at the same place.

`-f FILE` reads patterns from `FILE`, one per line (`-` reads them from
standard input), and can be repeated or mixed with `-e`; like `-e` it means
there is no positional pattern. A trailing carriage return is dropped from
each line, so files saved with Windows line endings work. A blank line in the
file is an empty pattern and matches every line, while an empty file has no
patterns at all and matches nothing, which keeps
`mgrep -vf known_errors.txt app.log` working even when the list is empty.

`-A N` prints up to `N` lines after each match and `-B N` up to `N` lines
before it; `-C N` sets both. A line is never printed twice when contexts
overlap. Context lines use `-` instead of `:` after the file name and line
number (`app.log-12-...`), and groups that are not next to each other are
separated by a `--` line, so `mgrep -n -A2 panic app.log` shows each panic
with the two lines that followed it, and `mgrep -C3 'def main' *.py` shows a
little of the code around each definition. With `-m` the trailing context of
the last match is still printed. Context is ignored with `-c` and `-o`.

`-l` prints each file name once, as soon as a selected line is found, and
`-L` prints the files where none was. For example `mgrep -L '#pragma once'
src/*.hpp` finds headers missing a guard. With `-l` or `-L` the exit status
is `0` when at least one name was printed.

## Layout

```
src/grep.hpp, src/grep.cpp   Matcher and scan(): the testable core
src/main.cpp                 command-line parsing and file handling
tests/tests.cpp              minimal self-contained test runner
tests/cli.sh                 exit-code and message checks for the binary
```
