#ifndef _VISITOR_H
#define _VISITOR_H

#include "expression.h"


#include "if_statement.h"
#include "while_statement.h"
#include "unary_operation.h"
#include "class_definition.h"
#include "function_definition.h"
#include "binary_operation.h"
#include "unary_operation.h"

class Visitor
{
public:
    virtual void visit(IfStatement&) = 0;
    virtual void visit(WhileStatement&) = 0;
    virtual void visit(UnaryOperation&) = 0;
    virtual void visit(ClassDef&) = 0;
    virtual void visit(FuncDef&) = 0;
    virtual void visit(BinaryOperation&) = 0;
};

#endif