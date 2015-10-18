#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include "ast.h"

class Expression : public AST
{
public:
    virtual ~Expression() = 0;
};

Expression::~Expression() {}

#endif
