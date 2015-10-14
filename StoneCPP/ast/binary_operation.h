#ifndef __BINARY_OPERATION_H
#define __BINARY_OPERATION_H

#include "ast_list.h"
#include <sstream>
#include "operators.h"
#include <cassert>

class BinaryOperation : public ASTList {
private:
    BinaryOperator op;

public:
    BinaryOperation(BinaryOperator op, ASTree* lhs, ASTree* rhs): ASTList({lhs, rhs}), op(op) {}

    BinaryOperator get_op()
    {
        return op;
    }

    ASTree* left_expr()
    {
        assert(this->num_children() == 2);
        return this->child(0);
    }

    ASTree* right_expr()
    {
        assert(this->num_children() == 2);
        return this->child(1);
    }

    // Inherited via ASTList
    virtual std::string toString() override
    {
        assert(this->num_children() == 2);
        std::ostringstream oss;
        oss << this->child(0)->toString() << op << this->child(1)->toString();

        return oss.str();
    }
};
#endif
