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
"$BIN" -f "$F" done 3
"$BIN" -f "$F" undo 3
expect "undo reopens task" "[ ] 3  (low) water plants" "$("$BIN" -f "$F" list --pending | tail -n 1)"
"$BIN" -f "$F" undo 99 2>/dev/null; expect "undo missing id exits 1" 1 $?
expect "find is case-insensitive" "[ ] 4  (high) pay rent" "$("$BIN" -f "$F" find RENT)"
"$BIN" -f "$F" find nothing-here >/dev/null; expect "find with no match exits 1" 1 $?
"$BIN" -f "$F" find 2>/dev/null; expect "find without text is usage error" 2 $?
"$BIN" -f "$F" done 3
expect "stats" "2 tasks, 1 done (50%), 1 pending
pending: 1 high, 0 normal, 0 low" "$("$BIN" -f "$F" stats)"
expect "stats on empty list" "0 tasks, 0 done (0%), 0 pending" "$("$BIN" -f "$DIR/none.txt" stats)"
"$BIN" -f "$F" list --all 2>/dev/null; expect "unknown list flag is usage error" 2 $?

"$BIN" help | head -n 1 | grep -q '^usage: todo'; expect "help prints usage" 0 $?
"$BIN" --help >/dev/null; expect "--help exits 0" 0 $?
"$BIN" -h 2>/dev/null | grep -q 'todo help'; expect "-h lists help command" 0 $?
G="$DIR/multi.txt"
for t in a b c d; do "$BIN" -f "$G" add "$t" >/dev/null; done
"$BIN" -f "$G" done 1 3
expect "done with several ids" "[ ] 2  b
[ ] 4  d" "$("$BIN" -f "$G" list --pending)"
"$BIN" -f "$G" rm 2 9 2>/dev/null; expect "rm with unknown id exits 1" 1 $?
expect "rm with unknown id changes nothing" 4 "$("$BIN" -f "$G" list | wc -l | tr -d ' ')"
"$BIN" -f "$G" rm 2 4
expect "rm with several ids" "[x] 1  a
[x] 3  c" "$("$BIN" -f "$G" list)"
"$BIN" -f "$G" undo 1 x 2>/dev/null; expect "bad id among several is usage error" 2 $?

expect "next picks highest priority" "[ ] 4  (high) pay rent" "$("$BIN" -f "$F" next)"
"$BIN" -f "$G" next >/dev/null; expect "next with nothing pending exits 1" 1 $?
expect "next with nothing pending" "nothing to do" "$("$BIN" -f "$G" next)"

"$BIN" -f "$G" add -p high e >/dev/null
"$BIN" -f "$G" add -p high f >/dev/null
"$BIN" -f "$G" done 4
expect "list -p filters by priority" "[x] 4  (high) e
[ ] 5  (high) f" "$("$BIN" -f "$G" list -p high)"
expect "list -p combines with --pending" "[ ] 5  (high) f" "$("$BIN" -f "$G" list -p h --pending)"
expect "list --done -p normal" "[x] 1  a
[x] 3  c" "$("$BIN" -f "$G" list --done -p normal)"
"$BIN" -f "$G" list -p 2>/dev/null; expect "list -p without level is usage error" 2 $?
"$BIN" -f "$G" list --pending --done 2>/dev/null; expect "list with both filters is usage error" 2 $?

[ $fail -eq 0 ] && echo "cli: all smoke tests passed"
exit $fail
