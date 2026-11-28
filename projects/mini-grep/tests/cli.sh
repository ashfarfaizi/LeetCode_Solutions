#!/bin/sh
# Smoke tests for the mgrep command line: exit codes and messages that the
# unit tests in tests.cpp cannot see. Usage: tests/cli.sh path/to/mgrep
set -u
MGREP=${1:-build/mgrep}
fail=0
pass=0

check() {  # check NAME EXPECTED ACTUAL
    if [ "$2" = "$3" ]; then
        pass=$((pass + 1))
    else
        fail=$((fail + 1))
        printf 'FAILED: %s\n  expected: %s\n  actual:   %s\n' "$1" "$2" "$3"
    fi
}

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
printf 'alpha\nbeta\n' > "$tmp/a.txt"

out=$("$MGREP" alpha "$tmp/a.txt"); check "match exit" "0" "$?"
check "match output" "alpha" "$out"
"$MGREP" gamma "$tmp/a.txt" > /dev/null; check "no match exit" "1" "$?"

err=$("$MGREP" alpha "$tmp/missing" 2>&1 > /dev/null); check "missing exit" "2" "$?"
check "missing message" "mgrep: $tmp/missing: cannot open file" "$err"

err=$("$MGREP" -s alpha "$tmp/missing" 2>&1 > /dev/null); check "-s exit" "2" "$?"
check "-s silences message" "" "$err"
out=$("$MGREP" -s alpha "$tmp/missing" "$tmp/a.txt" 2> /dev/null); check "-s other files" "2" "$?"
check "-s still scans other files" "$tmp/a.txt:alpha" "$out"

"$MGREP" -q -s alpha "$tmp/missing" "$tmp/a.txt"; check "-qs match wins" "0" "$?"
"$MGREP" -z alpha "$tmp/a.txt" 2> /dev/null; check "bad option" "2" "$?"

printf 'beta\r\ngamma\n' > "$tmp/pats"
out=$("$MGREP" -f "$tmp/pats" "$tmp/a.txt"); check "-f exit" "0" "$?"
check "-f reads patterns (CRLF ok)" "beta" "$out"
out=$("$MGREP" -f "$tmp/pats" -e alpha "$tmp/a.txt" | tr '\n' ' '); check "-f with -e" "alpha beta " "$out"
: > "$tmp/empty"
"$MGREP" -f "$tmp/empty" "$tmp/a.txt" > /dev/null; check "-f empty matches nothing" "1" "$?"
out=$("$MGREP" -v -f "$tmp/empty" "$tmp/a.txt" | wc -l | tr -d ' '); check "-vf empty selects all" "2" "$out"
"$MGREP" -f "$tmp/nope" "$tmp/a.txt" 2> /dev/null; check "-f missing file" "2" "$?"

mkdir -p "$tmp/d/sub" "$tmp/d/empty"
printf 'alpha one\n' > "$tmp/d/b.txt"
printf 'nothing\nalpha two\n' > "$tmp/d/sub/a.txt"
err=$("$MGREP" alpha "$tmp/d" 2>&1 > /dev/null); check "dir without -r exit" "2" "$?"
check "dir without -r message" "mgrep: $tmp/d: is a directory" "$err"
out=$("$MGREP" -rn alpha "$tmp/d" | tr '\n' '|'); check "-r exit" "0" "$?"
check "-r sorted with names" "$tmp/d/b.txt:1:alpha one|$tmp/d/sub/a.txt:2:alpha two|" "$out"
abs="$(cd "$(dirname "$MGREP")" && pwd)/$(basename "$MGREP")"
out=$(cd "$tmp/d/sub" && "$abs" -r alpha); check "-r defaults to ." "./a.txt:alpha two" "$out"
out=$("$MGREP" -rl two "$tmp/d"); check "-rl" "$tmp/d/sub/a.txt" "$out"
"$MGREP" -r alpha "$tmp/d/empty"; check "-r empty dir" "1" "$?"

printf 'alpha md\n' > "$tmp/d/notes.md"
out=$("$MGREP" -r --include='*.txt' alpha "$tmp/d" | tr '\n' '|'); check "--include" "$tmp/d/b.txt:alpha one|$tmp/d/sub/a.txt:alpha two|" "$out"
out=$("$MGREP" -r --exclude='*.txt' alpha "$tmp/d"); check "--exclude" "$tmp/d/notes.md:alpha md" "$out"
out=$("$MGREP" -rl --include='*.txt' --include='*.md' --exclude='a.*' alpha "$tmp/d" | tr '\n' '|'); check "--include/--exclude combine" "$tmp/d/b.txt|$tmp/d/notes.md|" "$out"
out=$("$MGREP" -r --include='?.txt' -c alpha "$tmp/d" | tr '\n' '|'); check "--include ?" "$tmp/d/b.txt:1|$tmp/d/sub/a.txt:1|" "$out"
out=$("$MGREP" --exclude='*.txt' alpha "$tmp/a.txt"); check "named files not filtered" "alpha" "$out"
"$MGREP" -r --include= alpha "$tmp/d" 2> /dev/null; check "--include= empty" "2" "$?"
mkdir -p "$tmp/d/.git" "$tmp/d/sub/build"
printf 'alpha git\n' > "$tmp/d/.git/config"
printf 'alpha obj\n' > "$tmp/d/sub/build/out.txt"
out=$("$MGREP" -rl alpha "$tmp/d" | wc -l | tr -d ' '); check "-r sees nested dirs" "5" "$out"
out=$("$MGREP" -rl --exclude-dir=.git --exclude-dir='b*d' alpha "$tmp/d" | tr '\n' '|'); check "--exclude-dir" "$tmp/d/b.txt|$tmp/d/notes.md|$tmp/d/sub/a.txt|" "$out"
err=$("$MGREP" -r --exclude-dir= alpha "$tmp/d" 2>&1 > /dev/null); check "--exclude-dir= empty" "2" "$?"
check "--exclude-dir= message" "mgrep: --exclude-dir needs a pattern" "$(echo "$err" | head -n 1)"

out=$("$MGREP" --help 2> /dev/null | head -n 1); check "--help exit" "0" "$?"
check "--help on stdout" "usage: mgrep [-bicnovwxlLqrsHh] [-m NUM] [-A NUM] [-B NUM] [-C NUM]" "$out"
err=$("$MGREP" --colour x "$tmp/a.txt" 2>&1 > /dev/null); check "unknown long option exit" "2" "$?"
check "unknown long option message" "mgrep: unknown option --colour" "$(echo "$err" | head -n 1)"
out=$("$MGREP" -- --help "$tmp/a.txt"); check "-- then --help is a pattern" "1" "$?"

echo "$pass/$((pass + fail)) cli checks passed"
[ "$fail" -eq 0 ]
