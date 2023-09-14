#ifndef TOKEN_H_
#define TOKEN_H_

#include "lex/quote/quote.h"
#include "lex/token/tokenkind.h"

typedef struct Token {
    Quote     quote;
    TokenKind kind;
} Token;

Token token_new(Quote quote, TokenKind kind);
void token_print(const Token* const token);

#endif