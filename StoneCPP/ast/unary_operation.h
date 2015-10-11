#ifndef __UNARY_OPERATION_H
#define __UNARY_OPERATION_H

#include "ast_list.h"
#include "operators.h"
#include <sstream>
#include <cassert>

class UnaryOperation : public ASTList{
private:
    UnaryOperator op;

public:
    UnaryOperation(UnaryOperator op, ASTree* operation): op(op), ASTList(operation) {}

    UnaryOperator get_op()
    {
        return op;
    }

    ASTree* expr()
    {
        assert(this->num_children() == 1);
        return this->child(0);
    }

    // Inherited via ASTList
    virtual std::string toString() override
    {
        assert(this->num_children() == 1);
        std::ostringstream oss;
        oss << op << this->child(0)->toString();
        
        return oss.str();
    }
};

#endif