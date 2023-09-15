#ifndef VEC_TOKEN_H_
#define VEC_TOKEN_H_
#include <stddef.h>
#include "lex/token/token.h"

typedef struct TokenVec {
    Token* tokens;
    size_t capacity;
    size_t length;
} TokenVec;

TokenVec token_vec_new(void);
void token_vec_destroy(TokenVec* const self);
void token_vec_push(TokenVec* const self, Token item);
const Token* token_vec_at(const TokenVec* const self, size_t index);
const Token* token_vec_last(const TokenVec* const self);
#endif