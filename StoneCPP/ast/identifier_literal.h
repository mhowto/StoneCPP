#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include "literal.h"
#include <string>
#include "postfix.h"

class Visitor;

class IdentifierLiteral : public Literal {
public:
    IdentifierLiteral() = default;
    IdentifierLiteral(std::string iden): identifier_name(iden) {}

    ~IdentifierLiteral()
    {
        for (std::vector<Statement*>::size_type i = 0; i < postfixs.size(); ++i)
        {
            delete postfixs[i];
        }
    }

    std::string value()
    { 
        return identifier_name;
    }

    std::string get_identifier() const
    {
        return identifier_name;
    }

    void set_identifier(std::string val)
    {
        identifier_name = val;
    }

    virtual std::vector<Postfix*> get_postfixs() const override
    {
        return postfixs;
    }

    void set_postfixs(std::vector<Postfix*> val)
    {
        postfixs = val;
    }

    virtual void push_postfix(Postfix* postfix) override
    {
        postfixs.push_back(postfix);
    }

    virtual void accept(Visitor& visitor) override;

private:
    std::string identifier_name;
    std::vector<Postfix*> postfixs;
};

#endif
