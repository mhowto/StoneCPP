#ifndef __NUMBER_LITERAL_H
#define __NUMBER_LITERAL_H

#include "ast_leaf.h"

class NumberLiteral : public ASTLeaf {
public:
    NumberLiteral() = default;
    NumberLiteral(int num): number(num) {}

    int value() { return  number; }

    virtual std::string toString() override
    {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

private:
    int number;
};

#endif