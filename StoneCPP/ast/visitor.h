#ifndef _VISITOR_H
#define _VISITOR_H


class IfStatement;
class WhileStatement;
class SimpleStatement;

class ClassDef;
class FuncDef;

class ArrayPostfix;
class CallPostfix;
class MemberPostfix;

class CallExpression;
class ArrayLiteral;
class StringLiteral;
class NumberLiteral;
class IdentifierLiteral;

class BinaryOperation;
class UnaryOperation;

class Block;

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