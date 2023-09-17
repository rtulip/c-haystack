#ifndef PARSER_ERROR_H_
#define PARSER_ERROR_H_

#include "slice/SliceTokenKind.h"
#include "lex/token/token.h"

typedef struct ParserErrorUnexpectedToken {
    const Token* const found;
    const ConstSliceTokenKind expected;
} ParserErrorUnexpectedToken;

typedef enum ParserErrorTag {
    PARSER_ERROR_TAG_UNEXPECTED_TOKEN,
} ParserErrorTag;

typedef union ParserErrorValue {
    ParserErrorUnexpectedToken unexpected_token;
} ParserErrorValue;

typedef struct ParserError {
    ParserErrorTag tag;
    ParserErrorValue value;
} ParserError;

ParserError parser_error_new_unexpected_token(const Token* const token, ConstSliceTokenKind expected);
void parser_error_report(const ParserError* const err);

#endif