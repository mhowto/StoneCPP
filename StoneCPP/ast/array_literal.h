#ifndef _ARRAY_LITERAL_H
#define _ARRAY_LITERAL_H

#include "literal.h"

class Expression;

class ArrayLiteral : public Literal
{
public:
    ArrayLiteral(std::vector<Expression*> _ele): elements(_ele) {}

    ~ArrayLiteral()
    {
        for (int i = 0; i < elements.size(); ++i)
        {
            delete elements[i];
        }
    }

    void push_arg(Expression* element)
    {
        elements.push_back(element);
    }

    std::vector<Expression*> get_elements() 
    {
        return elements;
    }

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
    std::vector<Expression*> elements;
};
#endif