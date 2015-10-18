#ifndef _FUNCTION_DEFITION_H
#define _FUNCTION_DEFITION_H

#include "ast.h"
#include "statement.h"
#include <string>
#include <sstream>
#include <algorithm>

class Statement;

class FuncDef : public AST
{
public:
    FuncDef(std::string identifier_, std::vector<std::string> params_) : identifier(identifier_), params(params_) {}

    ~FuncDef()
    {
        for (int i = 0; i < block.size(); ++i)
        {
            delete block[i];
        }
    }

    std::string get_identifier()
    {
        return identifier;
    }

    std::vector<std::string> get_params()
    {
        return params;
    }

    std::vector<Statement*> get_block()
    {
        return block;
    }

    void push_statment(Statement* stmt)
    {
        block.push_back(stmt);
    }

    virtual void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string identifier;
    std::vector<std::string> params;
    std::vector<Statement*> block;
};

#endif