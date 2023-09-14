#include "lex/scanner/scanner.h"
#include "tools/vec/token/vec.h"
#include "tools/sv/sv.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

static char _scanner_peek(const Scanner* const self, size_t offset)
{
    assert(self != NULL);
    assert(self->current - 1 + offset < self->source->length);
    return self->source->slice[self->current - 1 + offset];
}

static void _scanner_add_token(Scanner* const self, TokenKindTag kind)
{
    assert(self != NULL);
    StringView sv = sv_substring(self->source, self->start, self->current);
    switch (kind)
    {
        case TOKENKIND_TAG_LEFT_BRACE:

            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_left_brace()
            ));
            break;

        case TOKENKIND_TAG_RIGHT_BRACE:
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_right_brace()
            ));
            break;
        case TOKENKIND_TAG_LEFT_PAREN:
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_left_paren()
            ));
            break;
        case TOKENKIND_TAG_RIGHT_PAREN:
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_right_paren()
            ));
            break;
        case TOKENKIND_TAG_LEFT_BRACKET:
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_left_bracket()
            ));
            break;
        case TOKENKIND_TAG_RIGHT_BRACKET:
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_right_bracket()
            ));
            break;
        case TOKENKIND_TAG_IDENT:
        {              
            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_ident(sv)
            ));
            break;
        }
        case TOKENKIND_TAG_NUMBER:
        {
            uint32_t n = strtoul(sv.slice, NULL, 10);

            token_vec_push(&self->tokens, token_new(
                quote_new(
                    sv,
                    *self->filename,
                    self->line,
                    self->token_start,
                    self->token_end
                ),
                token_kind_new_number(n)
            ));
            break;
        }
        default:
            printf("Unknown tokenkindtag: %d\n", kind);
            exit(1);
            break;
    }

}

static void _scanner_newline(Scanner* const self)
{
    assert(self != NULL);
    self->line += 1;
    self->token_start = 1;
    self->token_end = 1;
}

static bool _should_advance_ident(const Scanner* self)
{
    switch (_scanner_peek(self, 1))
    {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
        case ':':
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
        case '<':
        case '>':
            return false;
        default:
            break;
    }

    return !_scanner_is_at_end(self);
}

static void _scanner_parse_ident(Scanner* const self)
{

    while (_should_advance_ident(self))
    {
        _scanner_advance(self);
    }
    
    _scanner_add_token(self, TOKENKIND_TAG_IDENT);

}

static void _scanner_parse_number(Scanner* const self)
{
    while (isdigit(_scanner_peek(self, 1)))
    {
        _scanner_advance(self);
    }

    _scanner_add_token(self, TOKENKIND_TAG_NUMBER);
}

static void _scanner_next_token(Scanner* const self)
{
    assert(self != NULL);

    const char c = _scanner_advance(self);
    switch (c)
    {
        case '[':
            _scanner_add_token(self, TOKENKIND_TAG_LEFT_BRACKET);
            break;
        case ']':
            _scanner_add_token(self, TOKENKIND_TAG_RIGHT_BRACKET);
            break;
        case '{':
            _scanner_add_token(self, TOKENKIND_TAG_LEFT_BRACE);
            break;
        case '}':
            _scanner_add_token(self, TOKENKIND_TAG_RIGHT_BRACE);
            break;
        case '(':
            _scanner_add_token(self, TOKENKIND_TAG_LEFT_PAREN);
            break;
        case ')':
            _scanner_add_token(self, TOKENKIND_TAG_RIGHT_PAREN);
            break;
        
        /**
         * do nothing for whitespace.
         */
        case ' ':
        case '\t':
        case '\r':
            break;

        case '\n':
            _scanner_newline(self);
            break;

        default:
        {
            if (isdigit(c))
            {
                _scanner_parse_number(self);
            }
            else if (isalpha(c) || c == '_')
            {
                _scanner_parse_ident(self);
            }
            else 
            {
                printf("ERROR: Not sure what to do with char `%c`\n", c);
                exit(1);
            }
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