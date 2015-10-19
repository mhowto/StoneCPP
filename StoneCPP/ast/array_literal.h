#ifndef _ARRAY_LITERAL_H
#define _ARRAY_LITERAL_H

#include "literal.h"
#include "expression.h"

class Visitor;

class ArrayLiteral : public Literal
{
public:
    ArrayLiteral(std::vector<Expression*> _ele): elements(_ele) {}

    ~ArrayLiteral()
    {
        for (std::vector<Statement*>::size_type  i = 0; i < elements.size(); ++i)
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

    virtual void accept(Visitor& visitor) override;
private:
    std::vector<Expression*> elements;
};
#endif