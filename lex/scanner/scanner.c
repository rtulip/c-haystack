#include "lex/scanner/scanner.h"
#include "tools/vec/token/vec.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Scanner {
    const StringView* const filename;
    const StringView* const source;
    TokenVec   tokens;

    size_t     start;
    size_t     current;
    size_t     line;
    size_t     token_start;
    size_t     token_end;
} Scanner;

static Scanner _scanner_init_alloc(const StringView* const  filepath, const StringView* const source)
{
    assert(filepath != NULL);
    assert(source != NULL);

    return (Scanner) {
        .filename = filepath,
        .source = source,
        .tokens = token_vec_new(),
        .start = 0,
        .current = 0,
        .line = 1,
        .token_start = 1,
        .token_end = 1,
    };
}

static bool _scanner_is_at_end(const Scanner* const self)
{
    assert(self != NULL);
    return self->current >= self->source->length;
}

static char _scanner_advance(Scanner* const self)
{
    assert(self != NULL);

    self->current += 1;
    self->token_end += 1;

    return self->source->slice[self->current - 1];
}

static void _scanner_next_token(Scanner* const self)
{
    assert(self != NULL);

    const char c = _scanner_advance(self);
    switch (c)
    {
        default:
        {
            printf("Scanner Error: Not sure what to do with `%c`\n", c);
            exit(1);
        }
    }
}

TokenVec scan_tokens_alloc(
    const StringView* const filepath, 
    const StringView* const  source
)
{

    Scanner scanner = _scanner_init_alloc(filepath, source);

    while (!_scanner_is_at_end(&scanner))
    {
        scanner.start = scanner.current;
        scanner.token_start = scanner.token_end;

        _scanner_next_token(&scanner);
    }

    return scanner.tokens;
}