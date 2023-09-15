#ifndef SCANNER_H_
#define SCANNER_H_

#include "sv/sv.h"
#include "vec/VecToken.h"
#include "either/EitherVecTokenOrScannerError.h"

EitherVecTokenOrScannerError scan_tokens_alloc(
    const StringView* const filepath, 
    const StringView* const  source
);

#endif