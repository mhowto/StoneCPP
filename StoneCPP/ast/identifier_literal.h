#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include "literal.h"
#include <string>
#include "visitor.h"

class Postfix;

class IdentifierLiteral : public Literal {
public:
    IdentifierLiteral() = default;
    IdentifierLiteral(std::string iden): identifier_name(iden) {}

    ~IdentifierLiteral()
    {
        for (int i = 0; i < postfixs.size(); ++i)
        {
            delete postfixs[i];
        }
    }

    std::string value()
    { 
        return identifier_name;
    }

    virtual std::vector<Postfix*> get_postfixs() override
    {
        return postfixs;
    }

    virtual void push_postfix(Postfix* postfix) override
    {
        postfixs.push_back(postfix);
    }

    virtual void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string identifier_name;
    std::vector<Postfix*> postfixs;
};

#endif