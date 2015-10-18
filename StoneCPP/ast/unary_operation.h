#ifndef __UNARY_OPERATION_H
#define __UNARY_OPERATION_H

#include "expression.h"
#include "operators.h"
#include <sstream>
#include <cassert>

class UnaryOperation : public Expression{
public:
    UnaryOperation(UnaryOperator op, AST* expr_): op(op), expression_(expr_) {}

    UnaryOperator get_op()
    {
        return op;
    }

    AST* expr()
    {
        return expression_;
    }

private:
    UnaryOperator op;
    AST* expression_;
};

#endif
