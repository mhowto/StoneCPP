#ifndef _BLOCK_H
#define _BLOCK_H

#include "ast.h"
#include "visitor.h"

class Statement;

class Block : public AST {
public:
    Block() = default;
    ~Block()
    {
        for (int i = 0; i < stmts.size(); ++i)
        {
            delete stmts[i];
        }
    }

    void push_statement(Statement* stmt)
    {
        stmts.push_back(stmt);
    }

    std::vector<Statement*> get_statements()
    {
        return stmts;
    }

    virtual void accept(Visitor& visitor)
    {
        visitor.visit(*this);
    }

private:
    std::vector<Statement*> stmts;
};

#endif