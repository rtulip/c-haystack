#ifndef LITERAL_EXPR_H_
#define LITERAL_EXPR_H_

#include "lex/token/token.h"
#include "sv/sv.h"

typedef struct ExprU32 {
    Token* Token;
    uint32_t value;
} ExprU32;

typedef struct ExprString {
    Token* Token;
    StringView* sv;
} ExprString;

#endif