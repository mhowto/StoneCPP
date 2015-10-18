#ifndef __UNARY_OPERATION_H
#define __UNARY_OPERATION_H

#include "expression.h"
#include "operators.h"
#include <sstream>
#include <cassert>
#include "visitor.h"

class UnaryOperation : public Expression{
public:
    UnaryOperation(UnaryOperator op, AST* expr_): op(op), expression_(expr_) {}

    UnaryOperator get_op()
    {
        return op;
    }

    AST* get_expr()
    {
        return expression_;
    }

    virtual void accept(Visitor& visitor) override;
private:
    UnaryOperator op;
    AST* expression_;
};

#endif
