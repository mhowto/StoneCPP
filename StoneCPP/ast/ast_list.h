#ifndef __AST_LIST_H
#define __AST_LIST_H

#include "ast_tree.h"
#include <vector>
#include <string>

class ASTList : public ASTree {
protected:
     std::vector<ASTree *> children;

public:
    virtual int num_children() override
    {
        return static_cast<int>(children.size());
    }

    // Inherited via ASTree
    virtual ASTree * child(unsigned int i) override
    {
        if (i >= children.size())
        {
            return nullptr;
        }
        return children[i];
    }

    virtual std::vector<ASTree*> get_children() override
    {
        return children;
    }

    virtual std::string location() override {
        for (auto& t : children)
        {
            std::string s = t->location();
            if (s != "")
                return s;
        }
        return nullptr;
    }

    ASTList(std::vector<ASTree *> list): children(list) {}

    ASTList(ASTree* child) : children({ child }) {}
};

#endif
