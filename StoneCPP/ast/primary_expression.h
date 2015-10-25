#ifndef _PRIMARY_EXPRESSION_H
#define _PRIMARY_EXPRESSION_H

#include "expression.h"
#include <vector>

class Postfix;

class PrimaryExpression :public Expression
{
public:
    PrimaryExpression() = default;
    virtual ~PrimaryExpression() = 0;
    virtual std::vector<Postfix*> get_postfixs() const = 0;
    virtual void push_postfix(Postfix*) = 0;
};

#endif
