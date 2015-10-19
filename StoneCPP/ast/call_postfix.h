#ifndef _CALL_POSTFIX_H
#define _CALL_POSTFIX_H

#include "postfix.h"
#include "identifier_literal.h"

class Visitor;

class CallPostfix : public Postfix
{
public:
    CallPostfix(std::vector<Expression*> _args): args(_args) {}
    ~CallPostfix()
    {
        for (std::vector<Statement*>::size_type  i = 0; i < args.size(); ++i)
        {
            delete args[i];
        }
    }

    virtual void accept(Visitor& visitor) override;

    std::vector<Expression*> get_args()
    {
        return args;
    }

    void push_arg(Expression* _arg)
    {
        args.push_back(_arg);
    }

private:
    std::vector<Expression*> args;
};

#endif