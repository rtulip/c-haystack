#ifndef SCANNER_ERROR_H_
#define SCANNER_ERROR_H_

#include "lex/quote/quote.h"

typedef enum ScannerErrorTag {
    SCANNER_ERROR_UNHANDLED_CHARACTER,
    SCANNER_ERROR_UNTERMINATED_STRING,
} ScannerErrorTag;

typedef union ScannerErrorValue {
    char unhandled_character;
} ScannerErrorValue;

typedef struct ScannerError {
    ScannerErrorTag tag;
    ScannerErrorValue value;
    Quote quote;
} ScannerError;

void scanner_error_report(const ScannerError* const error);

ScannerError scanner_error_new_unhandled_character(char character, Quote quote);
ScannerError scanner_error_new_unterminated_string(Quote quote);

#endif