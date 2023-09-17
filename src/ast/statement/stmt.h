#ifndef STATEMENT_H_
#define STATEMENT_H_

#include "ast/statement/function.h"

typedef enum StmtTag {
    STMT_TAG_FUNCTION,
} StmtTag;

typedef union StmtValue {
    FunctionStmt function;
} StmtValue;

typedef struct Stmt {
    StmtTag tag;
    StmtValue value;
} Stmt;

#endif