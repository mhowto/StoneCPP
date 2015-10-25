#include "include_all_ast.h"

AST::~AST() {}
Postfix::~Postfix() {}
Expression::~Expression() {}
Statement::~Statement() {}
Literal::~Literal() {}
PrimaryExpression::~PrimaryExpression() {}

std::ostream& operator<<(std::ostream& os, const UnaryOperator op)
{
    switch (op)
    {
    case UnaryOperator::NOT:   return os << "!";
    case UnaryOperator::PLUS:  return os << "+";
    case UnaryOperator::MINUS: return os << "-";
    case UnaryOperator::NONE: return os << "NONE";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const BinaryOperator op)
{
    switch (op)
    {
    case BinaryOperator::ADD:           return os << "+";
    case BinaryOperator::SUBSTRACT:     return os << "-";
    case BinaryOperator::MULTIPLY:      return os << "*";
    case BinaryOperator::DIVIDE:        return os << "/";
    case BinaryOperator::MODULO:        return os << "%";
    case BinaryOperator::LEFT_SHIFT:    return os << "<<";
    case BinaryOperator::RIGHT_SHIFT:   return os << ">>";
    case BinaryOperator::EQUAL:         return os << "==";
    case BinaryOperator::NOT_EQUAL:     return os << "!=";
    case BinaryOperator::LOWER:         return os << "<";
    case BinaryOperator::LOWER_EQUAL:   return os << "<=";
    case BinaryOperator::GREATER:       return os << ">";
    case BinaryOperator::GREATER_EQUAL: return os << ">=";
    case BinaryOperator::ASSIGN:        return os << "=";
    case BinaryOperator::OR:            return os << "||";
    case BinaryOperator::AND:           return os << "&&";
    case BinaryOperator::BITWISE_AND:   return os << "&";
    case BinaryOperator::BITWISE_OR:    return os << "|";
    case BinaryOperator::BITWISE_XOR:   return os << "^";
    case BinaryOperator::COMMA:         return os << ",";
    case BinaryOperator::NONE:          return os << "NONE";
    }
    return os;
}

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
