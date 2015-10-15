#ifndef __OPERATORS_H
#define __OPERATORS_H

#include <iostream>
#include <cassert>

enum class UnaryOperator
{
    NOT,
    PLUS,
    MINUS,
};

std::ostream& operator<<(std::ostream& os, const UnaryOperator op)
{
    switch (op)
    {
    case UnaryOperator::NOT:   return os << "!";
    case UnaryOperator::PLUS:  return os << "+";
    case UnaryOperator::MINUS: return os << "-";
    }
    assert(false);
}

enum class BinaryOperator
{
    ADD, SUBSTRACT, MULTIPLY, DIVIDE,
    MODULO,
    LEFT_SHIFT, RIGHT_SHIFT,
    EQUAL, NOT_EQUAL,
    LOWER, LOWER_EQUAL,
    GREATER, GREATER_EQUAL,
    ASSIGN, OR, AND,
    BITWISE_AND, BITWISE_OR, BITWISE_XOR,
    COMMA
};

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
    }
    assert(false);
}

#endif
