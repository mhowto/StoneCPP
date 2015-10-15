#ifndef __IF_STATEMENT_H
#define __IF_STATEMENT_H

#include "ast_list.h"
#include <sstream>

class IfStatement : public ASTList {
public:
    IfStatement(ASTree* expr, ASTree* if_block) : ASTList({ expr, if_block }) {}
    IfStatement(ASTree* expr, ASTree* if_block, ASTree* else_block) : ASTList({ expr, if_block, else_block }) {}
    
    ASTree* expr() 
    {
        return child(0);
    }

    ASTree* if_block()
    {
        return child(1);
    }

    ASTree* else_block()
    {
        if (num_children() == 3)
        {
            return child(2);
        }
        else
        {
            return nullptr;
        }
    }

    // Inherited via ASTList
    virtual std::string toString() override
    {
        std::stringstream oss;
        oss << "if" << expr()->toString() << if_block()->toString();
        if (ASTree* block = else_block())
        {
            oss << "else" << block->toString();
        }
        return oss.str();
    }
};

#endif
