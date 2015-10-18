#include "include_all_ast.h"

void Block::accept(Visitor& visitor) 
{
}

void IfStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void WhileStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void SimpleStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void ClassDef::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void FuncDef::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void ArrayPostfix::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void CallPostfix::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void MemberPostfix::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void CallExpression::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void ArrayLiteral::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void StringLiteral::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void NumberLiteral::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void IdentifierLiteral::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void BinaryOperation::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void UnaryOperation::accept(Visitor& visitor)
{
    visitor.visit(*this);
}