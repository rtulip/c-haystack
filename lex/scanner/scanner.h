#ifndef SCANNER_H_
#define SCANNER_H_

#include "tools/sv/sv.h"
#include "vec/VecToken.h"

VecToken scan_tokens_alloc(
    const StringView* const filepath, 
    const StringView* const  source
);

#endif