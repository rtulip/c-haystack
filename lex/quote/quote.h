#ifndef QUOTE_H_
#define QUOTE_H_
#include "tools/sv/sv.h"

typedef struct Quote {
    StringView lexeme;
    StringView filepath;
    size_t     line;
    size_t     row;
    size_t     column;
} Quote;

Quote quote_new(
    StringView lexeme,
    StringView filepath, 
    size_t line, 
    size_t row, 
    size_t column
);


#endif