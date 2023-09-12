#include "lex/scanner/scanner.h"
#include "tools/sv/sv.h"

int main() {

    StringView filepath = sv_new("file");
    StringView source   = sv_new("Hello World");

    TokenVec tokens = scan_tokens_alloc(&filepath, &source);

    token_vec_destroy(&tokens);

}