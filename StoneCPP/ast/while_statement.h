#ifndef _WHILE_STATEMENT_H
#define _WHILE_STATEMENT_H

#include "statement.h"
#include <sstream>
#include "visitor.h"

class Expression;

class WhileStatement : public Statement {
public:
    WhileStatement(Expression* expr, std::vector<Statement*> block) : expr_(expr), block_(block) {}
    ~WhileStatement()
    {
        delete expr_;
        for (int i = 0; i < block_.size(); ++i)
        {
            delete block_[i];
        }
    }

    Expression* expr()
    {
        return expr_;
    }

    std::vector<Statement*> block()
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