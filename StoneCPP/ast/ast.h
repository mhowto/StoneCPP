#ifndef __AST_H
#define __AST_H

#include <string>
#include <vector>

#include "visitor.h"

class AST {
public:
    virtual ~AST() = 0;
    virtual void accept(Visitor&) = 0;
};

AST::~AST() {} // must add this
#endif
