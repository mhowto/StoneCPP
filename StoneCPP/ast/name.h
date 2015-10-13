#ifndef __NAME_H
#define __NAME_H

#include "ast_leaf.h"
#include <string>

class Name : public ASTLeaf {
public:
    Name() = default;
    Name(std::string iden): identifier_name(iden) {}

    std::string name() { return identifier_name; }

    virtual std::string toString() override
    {
        return name();
    }

private:
    std::string identifier_name;
};

#endif