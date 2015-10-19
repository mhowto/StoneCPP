#ifndef _CALL_EXPRESSION_H
#define _CALL_EXPRESSION_H

#include "primary_expression.h"
#include "expression.h"
#include "postfix.h"

class Visitor;

class CallExpression : public PrimaryExpression
{
public:
    CallExpression(Expression* _expr): expr_(_expr) {}
    CallExpression(Expression* _expr, std::vector<Postfix*> postfixs_): expr_(_expr), postfixs(postfixs_) {}

    ~CallExpression()
    {
        delete expr_;
        for (std::vector<Statement*>::size_type  i = 0; i < postfixs.size(); ++i)
        {
            delete postfixs[i];
        }
    }

    Expression* get_expr()
    {
        return expr_;
    }

    virtual std::vector<Postfix*> get_postfixs() override
    {
        return postfixs;
    }

    virtual void push_postfix(Postfix* postfix) override
    {
        postfixs.push_back(postfix);
    }

    virtual void accept(Visitor& visitor) override;
private:
    Expression* expr_;
    std::vector<Postfix*> postfixs;
};

#endif