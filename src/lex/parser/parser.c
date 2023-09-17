#include "lex/parser/parser_error.h"
#include "lex/parser/parser.h"
#include "vec/VecToken.h"
#include "vec/VecStmt.h"
#include "lex/scanner/keywords.h"
#include "slice/SliceTokenKind.h"
#include "lex/token/token.h"
#include <stdbool.h>
#include <assert.h>

typedef struct Parser {
    const VecToken* const tokens;
    size_t                idx;
    VecStmt               stmts;
} Parser;

static bool _parser_is_at_end(const Parser* const self)
{
    assert(self != NULL);
    assert(self->idx < self->tokens->length);

    return vec_token_at(self->tokens, self->idx)->kind.tag == TOKENKIND_TAG_EOF;

}

static const Token* _parser_peek(const Parser* const self)
{
    assert(self != NULL);
    return vec_token_at(self->tokens, self->idx);
}

static EitherVecStmtOrParserError _parse_statement(Parser* const self)
{
    static const TokenKind expected[] = {
        (TokenKind){
            .tag = TOKENKIND_TAG_KEYWORD,
            .value.kw_id = KW_FN
        }
    };

    const Token* const token = _parser_peek(self);
    if (token_is_keyword(token, KW_FN))
    {
        assert(0 && "TODO: Parse Function");
    }
    
    ParserError err = parser_error_new_unexpected_token(
        token, 
        slice_tokenkind_new_const(expected)
    );

    return either_vec_stmt_or_parser_error_new_parser_error(err);

}

EitherVecStmtOrParserError parse(const VecToken* const tokens)
{

    static const TokenKind expected[] = {
        (TokenKind){
            .tag = TOKENKIND_TAG_KEYWORD,
            .value.kw_id = KW_FN
        }
    };

    Parser parser = {
        .stmts = vec_stmt_new(),
        .tokens = tokens,
        .idx = 0
    };

    while (!_parser_is_at_end(&parser))
    {
        EitherVecStmtOrParserError maybe_stmts = _parse_statement(&parser);
    }

    ParserError err = parser_error_new_unexpected_token(
        _parser_peek(&parser), 
        slice_tokenkind_new_const(expected)
    );

    return either_vec_stmt_or_parser_error_new_parser_error(err);

}