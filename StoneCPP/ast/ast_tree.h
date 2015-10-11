#ifndef __AST_TREE_H
#define __AST_TREE_H

#include <string>
#include <vector>

class ASTree {
public:
    virtual ASTree* child(unsigned int i) = 0;
    virtual int num_children() = 0;
    virtual std::vector<ASTree *> get_children() = 0;
    virtual std::string location() = 0;
    virtual std::string toString() = 0;
};
#endif