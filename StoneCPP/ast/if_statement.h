#ifndef __IF_STATEMENT_H
#define __IF_STATEMENT_H

#include "ast.h"
#include "statement.h"
#include <sstream>
#include "visitor.h"

class Expression;

class IfStatement : public Statement {
public:
    IfStatement() = default;
    IfStatement(Expression* expr, std::vector<Statement*> if_block) : expr_(expr), if_block_(if_block) {}
    
    IfStatement(Expression* expr, std::vector<Statement*> if_block, std::vector<Statement*> else_block) :
        expr_(expr), if_block_(if_block), else_block_(else_block) {}

    ~IfStatement()
    {

        delete expr_;
        for (int i = 0; i < if_block_.size(); ++i)
        {
            delete if_block_[i];
        }

        for (int i = 0; i < else_block_.size(); ++i)
        {
            delete else_block_[i];
        }
    }
    
    Expression* expr() 
    {
        return expr_;
    }

    std::vector<Statement*> if_block()
    {
        return if_block_;
    }

    std::vector<Statement*> else_block()
    {
        return else_block_;
    }

    void push_if_stmt(Statement* stmt)
    {
        if_block_.push_back(stmt);
    }

    void push_else_stmt(Statement* stmt)
    {
        else_block_.push_back(stmt);
    }

    // Inherited via Statement
    virtual void accept(Visitor & visitor) override
    {
        visitor.visit(*this);
    }
private:
    Expression* expr_;
    std::vector<Statement*> if_block_;
    std::vector<Statement*> else_block_;
};

#endif
