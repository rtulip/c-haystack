#include "lex/scanner/scanner_error.h"
#include <stdio.h>
#include <assert.h>

const char* _scanner_error_tag_to_string(ScannerErrorTag tag)
{
    switch (tag)
    {
        case SCANNER_ERROR_UNHANDLED_CHARACTER:
            return "Unexepected Character";
        case SCANNER_ERROR_UNTERMINATED_STRING:
            return "Unterminated String";
        default:
            return "Unknown";
    }
}

void scanner_error_report(const ScannerError* const error)
{
    assert(error != NULL);

    printf("%.*s:%lu:%lu: Scanner Error: %s\n", 
        (int)error->quote.filepath.length,
        error->quote.filepath.slice,
        error->quote.line,
        error->quote.row,
        _scanner_error_tag_to_string(error->tag)
    );

    switch (error->tag)
    {
        case SCANNER_ERROR_UNHANDLED_CHARACTER:
            printf("  * Not sure what to do with character `%c`\n", error->value.unhandled_character);
            break;
        case SCANNER_ERROR_UNTERMINATED_STRING:
            break;
        default:
            break;
    }

}

ScannerError scanner_error_new_unhandled_character(char character, Quote quote)
{
    return (ScannerError) {
        .tag = SCANNER_ERROR_UNHANDLED_CHARACTER,
        .value.unhandled_character = character,
        .quote = quote,
    };
}

ScannerError scanner_error_new_unterminated_string(Quote quote)
{
    return (ScannerError) {
        .tag = SCANNER_ERROR_UNTERMINATED_STRING,
        .quote = quote,
    };
}