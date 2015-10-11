#ifndef __STRING_LITERAL_H
#define __STRING_LITERAL_H

#include "ast_leaf.h"
#include <string>
#include <sstream>

class StringLiteral : public ASTLeaf {
public:
    StringLiteral(std::shared_ptr<Token> t) : ASTLeaf(t) {}

    std::string value() { return get_token()->getText(); }

    virtual std::string toString() override
    {
        std::ostringstream oss;
        oss << "\"" << value() << "\"";
        return oss.str();
    }
};

#endif