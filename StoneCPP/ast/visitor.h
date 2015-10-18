#ifndef _VISITOR_H
#define _VISITOR_H

#include "expression.h"
#include "block.h"

#include "if_statement.h"
#include "while_statement.h"
#include "simple_statement.h"

#include "unary_operation.h"
#include "class_definition.h"
#include "function_definition.h"
#include "binary_operation.h"
#include "unary_operation.h"

#include "array_postfix.h"
#include "call_postfix.h"
#include "member_postfix.h"

#include "call_expression.h"
#include "array_literal.h"
#include "string_literal.h"
#include "number_literal.h"
#include "identifier_literal.h"

class Visitor
{
public:
    virtual void visit(IfStatement&) = 0;
    virtual void visit(WhileStatement&) = 0;
    virtual void visit(SimpleStatement&) = 0;

    virtual void visit(ClassDef&) = 0;
    virtual void visit(FuncDef&) = 0;

    virtual void visit(ArrayPostfix&) = 0;
    virtual void visit(CallPostfix&) = 0;
    virtual void visit(MemberPostfix&) = 0;

    virtual void visit(CallExpression&) = 0;
    virtual void visit(ArrayLiteral&) = 0;
    virtual void visit(StringLiteral&) = 0;
    virtual void visit(NumberLiteral&) = 0;
    virtual void visit(IdentifierLiteral&) = 0;

    virtual void visit(BinaryOperation&) = 0;
    virtual void visit(UnaryOperation&) = 0;

    virtual void visit(Block&) = 0;
};

#endif