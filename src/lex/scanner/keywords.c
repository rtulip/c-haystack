#include "lex/scanner/keywords.h"
#include <assert.h>

static const char* keywords_table[] = {
    [KW_FN] = "fn",
};

KeywordId ident_is_keyword(const StringView* const ident)
{
    assert(ident != NULL);
    for (KeywordId id = 0; id < KW_END_OF_LIST; id++)
    {
        if (sv_equals(ident, keywords_table[id]))
        {
            return id;
        }
    }

    return KW_END_OF_LIST;

}