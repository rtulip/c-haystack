#include "lex/token/token.h"
#include <stdio.h>
#include <assert.h>

Token token_new(Quote quote, TokenKind kind)
{
    return (Token) {
        .quote = quote, 
        .kind = kind,
    };
}

bool token_is_keyword(const Token* const token, KeywordId kw)
{
    assert(token != NULL);
    if (token->kind.tag == TOKENKIND_TAG_KEYWORD)
    {
        return token->kind.value.kw_id == kw;
    }

    return false;
}

void token_print(const Token* const token)
{
    
    if (token != NULL)
    {
        printf(
            "%.*s:%ld:%ld: %s `%.*s`\n", 
            (int)token->quote.filepath.length,
            token->quote.filepath.slice,
            token->quote.line,
            token->quote.row,
            token_kind_tag_to_cstr(token->kind.tag),
            (int)token->quote.lexeme.length,
            token->quote.lexeme.slice
        );
    }
    else 
    {
        printf("Token: NULL");
    }
}