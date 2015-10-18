#ifndef __STRING_LITERAL_H
#define __STRING_LITERAL_H

#include "literal.h"
#include <string>
#include <sstream>

class Postfix;
class StringLiteral : public Literal {
public:
    StringLiteral() = default;
    StringLiteral(std::string s) : string_literal(s) {}

    std::string value() 
    { 
        return string_literal;
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
    std::string string_literal;
};

#endif