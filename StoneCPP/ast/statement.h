#ifndef _STATEMENT_H
#define _STATEMENT_H

#include "ast.h"

class Statement : public AST
{
public:
    virtual ~Statement() = 0;
};

#endif
