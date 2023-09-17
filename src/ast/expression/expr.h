#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "ast/expression/literal.h"

typedef enum ExprTag {
    EXPR_U32_LITERAL,
    EXPR_STRING_LITERAL,
} ExprTag;

typedef union ExprValue {
    ExprU32 u32;
    ExprString string;
} ExprValue;

typedef struct Expr {
    ExprTag tag;
    ExprValue value;
} Expr;

#endif