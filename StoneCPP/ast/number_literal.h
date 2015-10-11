#ifndef __NUMBER_LITERAL_H
#define __NUMBER_LITERAL_H

#include "ast_leaf.h"

class NumberLiteral : public ASTLeaf {
public:
    NumberLiteral(std::shared_ptr<Token> t) : ASTLeaf(t) {}

    int value() { return  get_token()->getValue(); }

    virtual std::string toString() override
    {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }
};

#endif