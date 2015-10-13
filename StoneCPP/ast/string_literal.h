#ifndef __STRING_LITERAL_H
#define __STRING_LITERAL_H

#include "ast_leaf.h"
#include <string>
#include <sstream>

class StringLiteral : public ASTLeaf {
public:
    StringLiteral() = default;
    StringLiteral(std::string s) : string_literal(s) {}

    std::string value() { return string_literal; }

    virtual std::string toString() override
    {
        std::ostringstream oss;
        oss << "\"" << value() << "\"";
        return oss.str();
    }

private:
    std::string string_literal;
};

#endif