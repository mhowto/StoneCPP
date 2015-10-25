#ifndef _FUNCTION_DEFITION_H
#define _FUNCTION_DEFITION_H

#include "ast.h"
#include "statement.h"
#include <string>

class Visitor;

class FuncDef : public AST
{
public:
    FuncDef(std::string identifier_, std::vector<std::string> params_) : identifier(identifier_), params(params_) {}
    FuncDef(std::string identifier_): identifier(identifier_) {}

    ~FuncDef()
    {
        for (std::vector<Statement*>::size_type  i = 0; i < block.size(); ++i)
        {
            delete block[i];
        }
    }

    std::string get_identifier() const
    {
        return identifier;
    }

    void set_identifier(std::string val)
    {
        identifier = val;
    }

    std::vector<std::string> get_params() const
    {
        return params;
    }

    void set_params(std::vector<std::string> val)
    {
        params = val;
    }

    std::vector<Statement*> get_block() const
    {
        return block;
    }

    void set_block(std::vector<Statement*> val)
    {
        block = val;
    }

    void push_statment(Statement* stmt)
    {
        block.push_back(stmt);
    }

    virtual void accept(Visitor& visitor) override;

private:
    std::string identifier;
    std::vector<std::string> params;
    std::vector<Statement*> block;
};

#endif
