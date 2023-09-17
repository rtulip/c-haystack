#include "lex/parser/parser_error.h"
#include <assert.h>

ParserError parser_error_new_unexpected_token(const Token* const token, ConstSliceTokenKind expected)
{
    assert(token != NULL);

    return (ParserError) {
        .tag = PARSER_ERROR_TAG_UNEXPECTED_TOKEN,
        .value.unexpected_token = (ParserErrorUnexpectedToken){
            .found = token,
            .expected = expected,
        }
    };

}

void parser_error_report(const ParserError* const err)
{
    (void)(err);
    assert(0 && "TODO: Not implemented yet");
}

