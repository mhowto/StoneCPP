#ifndef __BINARY_OPERATION_H
#define __BINARY_OPERATION_H

#include "expression.h"
#include <sstream>
#include "operators.h"
#include <cassert>
#include "visitor.h"

class BinaryOperation : public Expression {
public:
    BinaryOperation(BinaryOperator op, AST* lhs_, AST* rhs_): op(op), lhs(lhs_), rhs(rhs_) {}

    BinaryOperator get_op()
    {
        return op;
    }

    AST* left_expr()
    {
        return lhs;
    }

    AST* right_expr()
    {
        return rhs;
    }

    virtual void accept(Visitor& visitor) override;
private:
    BinaryOperator op;
    AST* lhs;
    AST* rhs;
};
#endif
