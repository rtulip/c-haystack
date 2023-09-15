#include "tools/vec/token/vec.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

TokenVec token_vec_new(void)
{
    return (TokenVec) {
        .capacity = 0,
        .length = 0,
        .tokens = NULL,
    };
}

void token_vec_destroy(TokenVec* const self)
{
    assert(self != NULL);
    free(self->tokens);
    *self = token_vec_new();
}

static bool _token_vec_at_capacity(const TokenVec* const self)
{
    assert(self != NULL);
    return (self->capacity == self->length);
}

static void _token_vec_expand(TokenVec* const self)
{
    /**
     * Increase the capacity of the vec.
     * 
     * If it's 0, then set it to 2.
     */
    self->capacity = self->capacity == 0 ?
        2 :
        self->capacity * 2;

    self->tokens = realloc(self->tokens, sizeof(Token) * self->capacity);
    
    assert(self->tokens != NULL);
}

void token_vec_push(TokenVec* const self, Token item)
{
    assert(self != NULL);
    if (_token_vec_at_capacity(self))
    {
        _token_vec_expand(self);
    }

    assert(self->tokens != NULL);
    self->tokens[self->length] = item;
    self->length += 1;
}

const Token* token_vec_at(const TokenVec* const self, size_t index)
{
    assert(self != NULL);
    assert(index < self->length);

    return &self->tokens[index];
}

const Token* token_vec_last(const TokenVec* const self)
{
    assert(self != NULL);

    if (self->length == 0)
    {
        return NULL;
    }
    else 
    {
        return &self->tokens[self->length-1];
    }

}