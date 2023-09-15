#include "sv.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

StringView sv_default(void)
{
    return (StringView) {
        .length = 0,
        .slice = "",
    };
}

/**
 * @brief Construct a new string view
 * 
 * @param string 
 * @return StringView 
 */
StringView sv_new(const char* string) {
    assert(string != NULL);
    StringView sv = {
        .length = strlen(string),
        .slice = string,
    };
    return sv;
}

StringView sv_read_from_file_alloc(const char* const filepath)
{
    assert(filepath != NULL);
    FILE* file = fopen(filepath, "r");

    if (file == NULL)
    {
        return sv_default();
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length == 0)
    {
        return sv_default();
    }

    char* buffer = malloc(length);
    if (buffer == NULL)
    {
        return sv_default();
    }

    fread(buffer, 1, length, file);
    fclose(file);

    return (StringView) {
        .length = length,
        .slice = buffer,
    };
    
}

/**
 * @brief Compares a string view to an empty string.
 * 
 * @param sv     - The view to compare 
 * @param string - The string to compare against 
 * @return true  - The view matches the input string
 * @return false - The view does not match the input string
 */
bool sv_equals(const StringView* const sv, const char* string)
{
    assert(sv != NULL);
    assert(string != NULL);

    return (strncmp(sv->slice, string, sv->length) == 0 && strlen(string) == sv->length);
}

/**
 * @brief Prints a string view to stdout
 * 
 * @param sv The view to print
 */
void sv_print(const StringView* const sv)
{
    assert(sv != NULL);
    printf("`%.*s`", (int)sv->length, sv->slice);
}

/**
 * @brief Prints a string view with a newline
 * 
 * @param sv - The view to print
 */
void sv_println( const StringView* const  sv)
{
    sv_print(sv);
    printf("\n");
}


/**
 * @brief Searches a string view for the pattern string & splits the view in
 *        two if the pattern is present, removing the matching pattern in the
 *        process.
 * 
 * @note This does modify the input `sv` if the `pattern` is present.
 * 
 * For example:
 * ```c
 * StringView sv = sv_new("Hello World");
 * StringView hello = sv_split_at_pattern(&sv, " ");
 * assert(sv_equals(&hello, "Hello"));
 * assert(sv_equals(&sv, "World"));
 * ```
 * 
 * If the pattern isn't present, then an empty string view will be returned.
 * ```
 * StringView sv = sv_new("Hello World");
 * StringView emtpy = sv_split_at_pattern(&sv, "Foo");
 * assert(sv_equals(&empty, ""));
 * ```
 * 
 * @param sv 
 * @param pattern 
 * @return StringView 
 */
StringView sv_split_at_pattern(StringView* const sv, const char* pattern)
{
    assert(sv != NULL);

    size_t pattern_len = strlen(pattern);

    for (int i = 0; i + pattern_len < sv->length; i++)
    {
        if (strncmp(sv->slice+i, pattern, pattern_len) == 0)
        {
            StringView new = {
                .length = i,
                .slice = sv->slice,
            };

            sv->slice += (i + pattern_len);
            sv->length -= (i + pattern_len);

            return new;
        }


    }

    return sv_new("");

}

StringView sv_substring(const StringView* const sv, size_t start, size_t end)
{

    assert(sv != NULL);
    if (start > sv->length)
    {
        assert(0 && "Start > Length");
    }

    if (end > sv->length)
    {
        assert(0 && "End > Length");
    }

    if (end < start )
    {
        assert(0 && "End < Start");
    }

    return (StringView){
        .length = end-start,
        .slice = (sv->slice) + start,
    };

}

static int _sv_print(
    FILE* stream,
    const struct printf_info* info,
    const void* const* args
)
{
    (void)(info);
    const StringView* sv = *((const StringView**)(args[0]));

    return fprintf(stream, "%.*s", (int)sv->length, sv->slice);
}

static int _sv_print_arginfo(
    const struct printf_info* info, 
    size_t n, 
    int* argtypes, 
    int* size
)
{
    (void)(info);
    if (n > 0)
    {
        argtypes[0] = PA_POINTER;
        size[0] = sizeof (StringView *);
    }
    return 1;
}

void register_sv_printf(void)
{
    register_printf_specifier('v', _sv_print, _sv_print_arginfo);
}