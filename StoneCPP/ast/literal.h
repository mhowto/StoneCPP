#ifndef _LITERAL_H
#define _LITERAL_H

#include "primary_expression.h"

class Literal : public PrimaryExpression
{
public:
    virtual ~Literal() = 0;
};

#endif
