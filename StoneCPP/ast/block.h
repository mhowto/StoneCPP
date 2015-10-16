#ifndef _BLOCK_H
#define _BLOCK_H

#include "ast_list.h"
#include <sstream>

class Block : public ASTList {
public:
    Block() = default;

    void push_statement(ASTree* stmt)
    {
        this->children.push_back(stmt);
    }

    virtual std::string toString() override
    {
        std::stringstream oss;
        oss << '{';
        if (num_children() > 1) {
            oss << child(0)->toString();
            for (int i = 1; i < num_children(); i++)
            {
                oss << ';' << child(i)->toString();
            }
        }
        oss << '}';
    }
};


#endif