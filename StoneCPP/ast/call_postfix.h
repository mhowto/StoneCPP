#ifndef _CALL_POSTFIX_H
#define _CALL_POSTFIX_H

#include "postfix.h"
#include "visitor.h"

class IdentifierLiteral;

class CallPostfix : public Postfix
{
public:
    CallPostfix(std::vector<Expression*> _args): args(_args) {}
    ~CallPostfix()
    {
        for (int i = 0; i < args.size(); ++i)
        {
            delete args[i];
        }
    }

    virtual void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

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