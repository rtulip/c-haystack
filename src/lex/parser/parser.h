#ifndef PARSER_H_
#define PARSER_H_

#include "either/EitherVecStmtOrParserError.h"
#include "vec/VecToken.h"

EitherVecStmtOrParserError parse(const VecToken* const tokens);


#endif