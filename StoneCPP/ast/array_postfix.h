#ifndef _ARRAY_POSTFIX_H
#define _ARRAY_POSTFIX_H

#include "postfix.h"
#include "visitor.h"

class Expression;

class ArrayPostfix : public Postfix
{
public:
    ArrayPostfix() = default;
    ArrayPostfix(Expression* _expr) : expr_(_expr) {}

    ~ArrayPostfix()
    {
        delete expr_;
    }

    Expression* get_expr()
    {
        return expr_;
    }

    virtual void accept(Visitor& visitor) override;
private:
    Expression* expr_;
};

#endif