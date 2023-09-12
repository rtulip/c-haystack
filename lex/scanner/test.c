#include "lex/scanner/scanner.h"
#include "tools/sv/sv.h"

int main() {

    StringView filepath = sv_new("file");
    StringView source   = sv_new("Hello World");

    TokenVec tokens = scan_tokens_alloc(&filepath, &source);

    for (int i = 0; i < tokens.length; i++)
    {
        const Token* token = token_vec_at(&tokens, i);
        printf("Token[%d]: %.*s\n", i, token->lexeme.length, token->lexeme.slice);
    }

    token_vec_destroy(&tokens);

}