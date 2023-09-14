#ifndef TOKENKIND_H_
#define TOKENKIND_H_
#include "tools/sv/sv.h"
#include "lex/scanner/keywords.h"
#include <stdint.h>

typedef enum TokenKindTag {
    TOKENKIND_TAG_LEFT_BRACE,
    TOKENKIND_TAG_RIGHT_BRACE,
    TOKENKIND_TAG_LEFT_PAREN,
    TOKENKIND_TAG_RIGHT_PAREN,
    TOKENKIND_TAG_LEFT_BRACKET,
    TOKENKIND_TAG_RIGHT_BRACKET,
    TOKENKIND_TAG_IDENT,
    TOKENKIND_TAG_NUMBER,
    TOKENKIND_TAG_KEYWORD,
    TOKENKIND_TAG_STRING,
} TokenKindTag;

typedef union TokenKindValue {
    StringView ident;
    uint64_t   number;
    KeywordId  kw_id;
    StringView string;
} TokenKindValue;

typedef struct TokenKind {
    TokenKindTag tag;
    TokenKindValue value;
} TokenKind;

const char* token_kind_tag_to_cstr(TokenKindTag tag);

TokenKind token_kind_new_left_brace(void);
TokenKind token_kind_new_right_brace(void);
TokenKind token_kind_new_left_paren(void);
TokenKind token_kind_new_right_paren(void);
TokenKind token_kind_new_left_bracket(void);
TokenKind token_kind_new_right_bracket(void);
TokenKind token_kind_new_ident(StringView ident);
TokenKind token_kind_new_number(uint64_t number);
TokenKind token_kind_new_keyword(KeywordId kw);
TokenKind token_kind_new_string(StringView sv);

#endif