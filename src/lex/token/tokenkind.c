#include "lex/token/tokenkind.h"
#include <stdio.h>
#include <assert.h>

const char* token_kind_tag_to_cstr(TokenKindTag tag)
{
    switch(tag)
    {
        case TOKENKIND_TAG_LEFT_BRACE:
            return "TOKENKIND_TAG_LEFT_BRACE";
        case TOKENKIND_TAG_RIGHT_BRACE:
            return "TOKENKIND_TAG_RIGHT_BRACE";
        case TOKENKIND_TAG_LEFT_PAREN:
            return "TOKENKIND_TAG_LEFT_PAREN";
        case TOKENKIND_TAG_RIGHT_PAREN:
            return "TOKENKIND_TAG_RIGHT_PAREN";
        case TOKENKIND_TAG_LEFT_BRACKET:
            return "TOKENKIND_TAG_LEFT_BRACKET";
        case TOKENKIND_TAG_RIGHT_BRACKET:
            return "TOKENKIND_TAG_RIGHT_BRACKET";
        case TOKENKIND_TAG_IDENT:
            return "TOKENKIND_TAG_IDENT";
        case TOKENKIND_TAG_NUMBER:
            return "TOKENKIND_TAG_NUMBER";
        case TOKENKIND_TAG_KEYWORD:
            return "TOKENKIND_TAG_KEYWORD";
        case TOKENKIND_TAG_STRING:
            return "TOKENKIND_TAG_STRING";
        default:
            printf("ERROR: Unknown token kind tag: %d", tag);
            assert(0 && "Unknown token kind tag");
    }
}

TokenKind token_kind_new_left_brace(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_LEFT_BRACE,
    };
}

TokenKind token_kind_new_right_brace(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_RIGHT_BRACE,
    };
}

TokenKind token_kind_new_left_paren(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_LEFT_PAREN,
    };    
}

TokenKind token_kind_new_right_paren(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_RIGHT_PAREN,
    };    
}

TokenKind token_kind_new_left_bracket(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_LEFT_BRACKET,
    };    
}

TokenKind token_kind_new_right_bracket(void)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_RIGHT_BRACKET,
    };    
}

TokenKind token_kind_new_ident(StringView ident)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_IDENT,
        .value.ident = ident,
    };    
}

TokenKind token_kind_new_number(uint64_t number)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_NUMBER,
        .value.number = number,
    };    
}


TokenKind token_kind_new_keyword(KeywordId kw)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_KEYWORD,
        .value.kw_id = kw,
    };
}

TokenKind token_kind_new_string(StringView sv)
{
    return (TokenKind) {
        .tag = TOKENKIND_TAG_STRING,
        .value.string = sv,
    };
}