#include "tools/vec/token/vec.h"
#include <assert.h>
#include <stdio.h>

int main() {

    TokenVec vec = token_vec_new();
    assert(vec.tokens == NULL);
    assert(vec.capacity == 0);
    assert(vec.length == 0);

    token_vec_push(&vec, (Token){.lexeme = sv_new("Example1")});

    assert(vec.tokens != NULL);
    assert(vec.capacity == 2);
    assert(vec.length == 1);
    assert(sv_equals(&vec.tokens[0].lexeme, "Example1"));

    token_vec_destroy(&vec);

    printf("Finished test\n");

}