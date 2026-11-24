# json-tokenizer

A small header-only C++17 tokenizer (lexer) for JSON text as defined by
RFC 8259. It turns a JSON document into a flat stream of tokens — the first
stage of a parser, a pretty-printer or a syntax highlighter.

## Features

- Punctuation tokens `{ } [ ] : ,` and the literals `true`, `false`, `null`
- Strings decoded with the standard escapes (`\" \\ \/ \b \f \n \r \t`);
  raw control characters are rejected
- Numbers validated against the JSON grammar (no leading zeros, no bare
  `.`, exponent must have digits) and returned exactly as written
- Every token records its byte offset; errors throw `jt::TokenizeError`
  with the offending offset

## Build and test

```sh
make test          # builds build/tests with -Wall -Wextra and runs it
```

or without make:

```sh
mkdir -p build && g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o build/tests && ./build/tests
```

## Usage

```cpp
#include "json_tokenizer.hpp"

jt::Tokenizer lexer(R"({"answer": 42})");
for (auto tok = lexer.next(); tok.type != jt::TokenType::End; tok = lexer.next())
    std::printf("%s %s\n", jt::type_name(tok.type), tok.value.c_str());
```
