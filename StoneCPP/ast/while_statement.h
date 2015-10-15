#ifndef _WHILE_STATEMENT_H
#define _WHILE_STATEMENT_H

#include "ast_list.h"
#include <sstream>


class WhileStatement : public ASTList {
public:
    WhileStatement(ASTree* expr, ASTree* block): ASTList({expr, block}) {}

    ASTree* expr() {
        return child(0);
    }

    ASTree* block() {
        return child(1);
    }

    virtual std::string toString() override
    {
        std::stringstream oss;
        oss << "while" << expr()->toString() << block()->toString();
        return oss.str();
    }
};

#endif