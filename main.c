#include "tools/sv/sv.h"
#include "lex/scanner/scanner.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(void)
{
    printf("Usage: `make run file=<file>`\n");
}

int main(int argc, const char** argv) {

    register_sv_printf();

    if (argc != 2)
    {
        printf("ERROR: Expected a file to compile\n");
        usage();
        return -1;
    }

    StringView filepath = sv_new(argv[0]);
    StringView source = sv_read_from_file_alloc(filepath.slice);
        
    TokenVec tokens = scan_tokens_alloc(&filepath, &source);
    
    token_vec_destroy(&tokens);
    free((void*) source.slice);
        

    return 0;
}