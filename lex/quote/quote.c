#include "lex/quote/quote.h"

Quote quote_new(
    StringView lexeme,
    StringView filepath, 
    size_t line, 
    size_t row, 
    size_t column
)
{
    return (Quote){
        .lexeme = lexeme,
        .filepath = filepath,
        .line = line,
        .row = row,
        .column = column,
    };
}