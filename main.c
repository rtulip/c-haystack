#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(void)
{
    printf("Usage: `make run file=<file>`\n");
}

int main(int argc, const char** argv) {

    int exit_code = 0;

    do {
        if (argc != 2)
        {
            printf("ERROR: Expected a file to compile\n");
            usage();
            exit_code = -1;
            break;
        }


        const char* file_path = argv[1];
        printf("File: %s\n", file_path);
        FILE* file = fopen(file_path, "r");

        if (file == NULL)
        {
            printf("ERROR: Failed to open file: `%s`\n", argv[1]);
            usage();
            exit_code = -1;
            break;
        }

        // File is open and must be closed
        do {

            fseek (file, 0, SEEK_END);
            size_t length = ftell (file);
            fseek (file, 0, SEEK_SET);

            char* buffer = malloc(length);
            if (buffer == NULL)
            {
                printf("ERROR: Failed to allocate space to read file.\n");
                exit_code = -1;
                break;
            }

            printf("Length: %ld\n", length);
            
            do {
                fread(buffer, 1, length, file);
                
                printf("%s\n", buffer);

            } while (0); // free the buffer

            free(buffer);

        } while(0); // Close file

        fclose(file);
        
    } while (0);

    return exit_code;
}