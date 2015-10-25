#ifndef _POSTFIX_H
#define _POSTFIX_H

#include "ast.h"

class Postfix : public AST
{
public:
    virtual ~Postfix() = 0;
};

#endif
