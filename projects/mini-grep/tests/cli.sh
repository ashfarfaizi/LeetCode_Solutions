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

echo "$pass/$((pass + fail)) cli checks passed"
[ "$fail" -eq 0 ]
