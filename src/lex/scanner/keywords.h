#ifndef KEYWORDS_H_
#define KEYWORDS_H_
#include "sv/sv.h"

typedef enum KeywordId {
    KW_FN,
    KW_END_OF_LIST, 
} KeywordId;

KeywordId ident_is_keyword(const StringView* const ident);


#endif