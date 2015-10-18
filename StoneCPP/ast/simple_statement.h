#ifndef _SIMPLE_STATEMENT_H
#define _SIMPLE_STATEMENT_H


#include "statement.h"
#include "visitor.h"

class Expression;

class SimpleStatement : public Statement {
public:
    SimpleStatement(Expression* _expr, std::vector<Expression*> _args): expr_(_expr), args_(_args) {}
    SimpleStatement(Expression* _expr): expr_(_expr) {}

    ~SimpleStatement()
    {
        delete expr_;
        for (int i = 0; i < args_.size(); ++i)
        {
            delete args_[i];
        }
    }

    Expression* get_expr()
    {
        return expr_;
    }

    std::vector<Expression*> get_args()
    {
        return args_;
    }

    void push_arg(Expression* _arg)
    {
        args_.push_back(_arg);
    }

    virtual void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    Expression* expr_;
    std::vector<Expression*> args_;
};
#endif