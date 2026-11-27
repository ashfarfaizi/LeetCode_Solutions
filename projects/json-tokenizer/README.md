# json-tokenizer

A small header-only C++17 tokenizer (lexer) for JSON text as defined by
RFC 8259. It turns a JSON document into a flat stream of tokens — the first
stage of a parser, a pretty-printer or a syntax highlighter.

## Features

- Punctuation tokens `{ } [ ] : ,` and the literals `true`, `false`, `null`
- Strings decoded with the standard escapes (`\" \\ \/ \b \f \n \r \t`);
  raw control characters are rejected
- `\uXXXX` escapes decoded to UTF-8, including surrogate pairs for
  characters outside the Basic Multilingual Plane
- Numbers validated against the JSON grammar (no leading zeros, no bare
  `.`, exponent must have digits) and returned exactly as written
- Every token records its byte offset and 1-based line and column; errors
  throw `jt::TokenizeError` with the same position, e.g.
  `invalid literal, expected 'null' at line 3, column 3`
- `jt::validate` / `jt::is_valid` (`json_validate.hpp`) check that the
  token stream forms exactly one JSON value, with an explicit stack (no
  recursion) and an optional maximum nesting depth
- `jt::minify` (`json_format.hpp`) strips insignificant whitespace from a
  valid document; `jt::escape_string` re-encodes a decoded string value as
  a JSON string literal
- `jt::pretty(src, indent)` re-indents a valid document with one element
  or member per line (default indent 2); empty `{}` / `[]` stay compact

## Build and test

```sh
make               # builds build/jtok and runs all tests
make test          # unit tests (build/tests) plus CLI smoke tests
```

or without make:

```sh
mkdir -p build && g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o build/tests && ./build/tests
g++ -std=c++17 -Wall -Wextra -Iinclude src/jtok.cpp -o build/jtok
```

## Command-line tool

`jtok` prints one token per line, or with `--check` only validates. It reads
a file argument or standard input and exits with 0 (valid), 1 (invalid JSON)
or 2 (usage / I/O error). `--minify` prints the document on one line and
`--pretty[=N]` re-indents it (default 2 spaces); only one mode may be given.

```console
$ echo '{"a": [1, true]}' | ./build/jtok
1:1 LBrace {
1:2 String "a"
1:5 Colon :
1:7 LBracket [
1:8 Number 1
1:9 Comma ,
1:11 True true
1:15 RBracket ]
1:16 RBrace }
$ echo '[1,]' | ./build/jtok --check
<stdin>:1:4: error: expected a value but found ']' at line 1, column 4
$ echo '{"a": [1, {}]}' | ./build/jtok --pretty
{
  "a": [
    1,
    {}
  ]
}
```

## Usage

```cpp
#include "json_tokenizer.hpp"

jt::Tokenizer lexer(R"({"answer": 42})");
for (auto tok = lexer.next(); tok.type != jt::TokenType::End; tok = lexer.next())
    std::printf("%s %s\n", jt::type_name(tok.type), tok.value.c_str());
```
