#ifndef _WHILE_STATEMENT_H
#define _WHILE_STATEMENT_H

#include "statement.h"
#include <sstream>
#include "expression.h"

class Visitor;

class WhileStatement : public Statement {
public:
    WhileStatement(Expression* expr) : expr_(expr) {}
    WhileStatement(Expression* expr, std::vector<Statement*> block) : expr_(expr), block_(block) {}
    ~WhileStatement()
    {
        delete expr_;
        for (std::vector<Statement*>::size_type i = 0; i < block_.size(); ++i)
        {
            delete block_[i];
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

    void set_block(std::vector<Statement*> val)
    {
        block_ = val;
    }

    std::vector<Statement*> get_block() const
    {
        return block_;
    }

    void push_stmt(Statement* stmt)
    {
        block_.push_back(stmt);
    }

    virtual void accept(Visitor& visitor) override;

private:
    Expression* expr_;
    std::vector<Statement*> block_;
};

#endif
