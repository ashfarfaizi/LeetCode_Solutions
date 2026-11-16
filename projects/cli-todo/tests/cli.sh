#!/bin/sh
# Smoke tests for the todo binary. Usage: sh tests/cli.sh path/to/todo
set -u
BIN=$1
DIR=$(mktemp -d)
trap 'rm -rf "$DIR"' EXIT
F="$DIR/t.txt"
fail=0

expect() {  # expect DESCRIPTION EXPECTED ACTUAL
    if [ "$2" != "$3" ]; then
        echo "cli: FAILED: $1"; echo "  expected: $2"; echo "  actual:   $3"
        fail=1
    fi
}

expect "add prints id" "added 1" "$("$BIN" -f "$F" add buy milk)"
"$BIN" -f "$F" add call mum >/dev/null
"$BIN" -f "$F" done 1
expect "list" "[x] 1  buy milk
[ ] 2  call mum" "$("$BIN" -f "$F" list)"
expect "TODO_FILE env" "[x] 1  buy milk
[ ] 2  call mum" "$(TODO_FILE="$F" "$BIN" list)"
"$BIN" -f "$F" done 9 2>/dev/null; expect "done missing id exits 1" 1 $?
"$BIN" -f "$F" done abc 2>/dev/null; expect "bad id is usage error" 2 $?
"$BIN" -f "$F" 2>/dev/null; expect "no command is usage error" 2 $?
"$BIN" -f "$F" edit 2 call dad
"$BIN" -f "$F" add water plants >/dev/null
"$BIN" -f "$F" rm 1
expect "edit and rm" "[ ] 2  call dad
[ ] 3  water plants" "$("$BIN" -f "$F" list)"
"$BIN" -f "$F" rm 1 2>/dev/null; expect "rm missing id exits 1" 1 $?
"$BIN" -f "$F" edit 2 2>/dev/null; expect "edit without text is usage error" 2 $?

[ $fail -eq 0 ] && echo "cli: all smoke tests passed"
exit $fail
