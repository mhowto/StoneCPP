#ifndef __NUMBER_LITERAL_H
#define __NUMBER_LITERAL_H

#include "literal.h"
#include "visitor.h"
class Postfix;

class NumberLiteral : public Literal {
public:
    NumberLiteral() = default;
    NumberLiteral(int num): number(num) {}

    int value() { return  number; }

    virtual std::vector<Postfix*> get_postfixs() override
    {
        return std::vector<Postfix*>();
    }

    virtual void push_postfix(Postfix* postfix) override
    {
    }

    virtual void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    int number;
};

#endif