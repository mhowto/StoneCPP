#ifndef _OPERATORS_H
#define _OPERATORS_H

#include <iostream>

enum class UnaryOperator
{
    NOT,
    PLUS,
    MINUS,
    NONE
};

std::ostream& operator<<(std::ostream& os, const UnaryOperator op);

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
    COMMA,
    NONE
};

std::ostream& operator<<(std::ostream& os, const BinaryOperator op);

#endif
