#ifndef __NAME_H
#define __NAME_H

#include "ast_leaf.h"
#include <string>

class Name : public ASTLeaf {
public:
    Name(std::shared_ptr<Token> t): ASTLeaf(t) {}

    std::string name() { return get_token()->getText(); }

    virtual std::string toString() override
    {
        return name();
    }
};

#endif