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
"$BIN" -f "$F" add -p high pay rent >/dev/null
"$BIN" -f "$F" pri 3 low
expect "list sorted by priority" "[ ] 4  (high) pay rent
[ ] 2  call dad
[ ] 3  (low) water plants" "$("$BIN" -f "$F" list)"
"$BIN" -f "$F" pri 3 urgent 2>/dev/null; expect "bad level is usage error" 2 $?
"$BIN" -f "$F" done 2
expect "list --pending" "[ ] 4  (high) pay rent
[ ] 3  (low) water plants" "$("$BIN" -f "$F" list --pending)"
expect "list --done" "[ ] 2  call dad" "$("$BIN" -f "$F" list --done | tr x ' ')"
expect "clear" "cleared 1 task" "$("$BIN" -f "$F" clear)"
expect "clear again" "cleared 0 tasks" "$("$BIN" -f "$F" clear)"
expect "list after clear" "[ ] 4  (high) pay rent
[ ] 3  (low) water plants" "$("$BIN" -f "$F" list)"
"$BIN" -f "$F" list --all 2>/dev/null; expect "unknown list flag is usage error" 2 $?

[ $fail -eq 0 ] && echo "cli: all smoke tests passed"
exit $fail
