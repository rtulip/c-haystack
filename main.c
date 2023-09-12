#include "tools/sv/sv.h"
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

    const char* filepath = argv[1];
    printf("File: %s\n", filepath);
    StringView file_sv = sv_read_from_file_alloc(filepath);
    {
        printf("%v\n", &file_sv);
    }
    free((void*) file_sv.slice);
        

    return 0;
}