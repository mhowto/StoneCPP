#ifndef __IF_STATEMENT_H
#define __IF_STATEMENT_H

#include "ast.h"
#include "statement.h"
#include <sstream>
#include "expression.h"

class Visitor;

class IfStatement : public Statement {
public:
    IfStatement() = default;
    IfStatement(Expression* expr) : expr_(expr) {}
    IfStatement(Expression* expr, std::vector<Statement*> if_block) : expr_(expr), if_block_(if_block) {}
    
    IfStatement(Expression* expr, std::vector<Statement*> if_block, std::vector<Statement*> else_block) :
        expr_(expr), if_block_(if_block), else_block_(else_block) {}

    ~IfStatement()
    {
        delete expr_;
        for (std::vector<Statement*>::size_type i = 0; i < if_block_.size(); ++i)
        {
            delete if_block_[i];
        }

        for (std::vector<Statement*>::size_type  i = 0; i < else_block_.size(); ++i)
        {
            delete else_block_[i];
        }
    }
    
    Expression* get_expr() const
    {
        return expr_;
    }

    void set_expr(Expression* val)
    {
        expr_ = val;
    }

    std::vector<Statement*> get_if_block() const
    {
        return if_block_;
    }

    void set_if_block(std::vector<Statement*> val)
    {
        if_block_ = val;
    }

    std::vector<Statement*> get_else_block() const
    {
        return else_block_;
    }

    void set_else_block(std::vector<Statement*> val)
    {
        else_block_ = val;
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
    virtual void accept(Visitor & visitor) override;
private:
    Expression* expr_;
    std::vector<Statement*> if_block_;
    std::vector<Statement*> else_block_;
};

#endif
