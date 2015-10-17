#ifndef __AST_H
#define __AST_H

#include <string>
#include <vector>

class AST {
public:
    virtual std::string location() = 0;
    virtual std::string toString() = 0;
    virtual ~AST() = 0;
};
#endif
