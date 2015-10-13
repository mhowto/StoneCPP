#ifndef __AST_LEAF_H
#define __AST_LEAF_H

#include "ast_tree.h"
#include "../token.h"
#include <string>
#include <memory>

class ASTLeaf : public ASTree {
//protected:
//    std::shared_ptr<Token> token;

public:
    // Inherited via ASTree
    virtual ASTree * child(unsigned int i) override
    {
        return nullptr;
    }

    virtual int num_children() override
    {
        return 0;
    }

    virtual std::vector<ASTree*> get_children() override
    {
        return std::vector<ASTree*>();
    }

    virtual std::string location() override
    {
        //return std::to_string(token->getLineNumber()) + ':' + std::to_string(token->getColumnNumber());
        return "unknown";
    }

    /*
    ASTLeaf(std::shared_ptr<Token> t): token(t) {}

    ASTLeaf(): token(nullptr) {}

    std::shared_ptr<Token> get_token()
    {
        return token;
    }
    */
};
#endif