#include "sv/sv.h"
#include "lex/scanner/scanner.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(void)
{
    printf("Usage: `make run file=<file>`\n");
}

int main(int argc, const char** argv)
{

    if (argc != 2)
    {
        printf("ERROR: Expected a file to compile\n");
        usage();
        return -1;
    }

    StringView filepath = sv_new(argv[1]);
    StringView source = sv_read_from_file_alloc(filepath.slice);
        
    printf("Source:\n%.*s\n", (int)source.length, source.slice);
    
    EitherVecTokenOrScannerError maybe_tokens = scan_tokens_alloc(&filepath, &source);
    if (either_vec_token_or_scanner_error_is_scanner_error(&maybe_tokens))
    {
        ScannerError err = either_vec_token_or_scanner_error_unpack_scanner_error(&maybe_tokens);
        scanner_error_report(&err);
        exit(1);
    }

    VecToken tokens = either_vec_token_or_scanner_error_unpack_vec_token(&maybe_tokens);

    for (size_t i = 0; i < tokens.length; i++)
    {
        const Token* const tok = vec_token_at(&tokens, i);
        token_print(tok);
    }

    vec_token_destroy(&tokens);
    free((void*) source.slice);
        

    return 0;
}