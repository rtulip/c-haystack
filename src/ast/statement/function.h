#ifndef FUNCTION_STMT_H_
#define FUNCITON_STMT_H_

#include "lex/token/token.h"
#include "ast/expression/expr.h"

typedef struct FunctionStmt {
    Token* fn_keyword;
    Token* fn_name_ident;
    Expr   body;
} FunctionStmt;

#endif