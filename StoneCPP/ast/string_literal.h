#ifndef __STRING_LITERAL_H
#define __STRING_LITERAL_H

#include "literal.h"
#include <string>
#include <sstream>
#include "visitor.h"

class Postfix;
class StringLiteral : public Literal {
public:
    StringLiteral() = default;
    StringLiteral(std::string s) : string_literal(s) {}

    std::string value() 
    { 
        return string_literal;
    }

    virtual std::vector<Postfix*> get_postfixs() const override
    {
        return std::vector<Postfix*>();
    }

    virtual void push_postfix(Postfix* postfix) override
    {
    }

    virtual void accept(Visitor& visitor) override;

private:
    std::string string_literal;
};

#endif