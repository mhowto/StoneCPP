#pragma once
#ifndef __TOKEN__H
#define __TOKEN__H

#include <string>

class Token
{
public:
    enum class TokenType {
        NUMBER,
        STRING,
        IDENTIFIER
    };

    Token(std::string file_name, int line_number, int column_number, TokenType type):
        file_name(file_name), line_number(line_number), column_number(column_number), type(type) {}

    TokenType getType() const
    {
        return this->type;
    }

    std::string getFileName() const {
        return file_name;
    }

    int getLineNumber() const {
        return line_number;
    }

    int getColumnNumber() const {
        return column_number;
    }

    int getValue() const {
        return -7777;
    }

    std::string getText() const
    {
        return "UNKNOWN TEXT";
    }

private:
    std::string file_name;
    int line_number;
    int column_number;

    TokenType type;
};

class NumToken : public Token {
public:
    NumToken(std::string file_name, int line_number, int column_number, std::string text) : 
        Token(file_name, line_number, column_number, TokenType::NUMBER), value(std::stoi(text)) {}

    int getValue() const
    {
        return value;
    }

private:
    int value;
};

class StrToken : public Token {
public:
    StrToken(std::string file_name, int line_number, int column_number, std::string text) : 
        Token(file_name, line_number, column_number, TokenType::STRING), literal(text) {}

    std::string getText() const
    {
        return literal;
    }

private:
    std::string literal;
};

class IdToken : public Token {
public:
    IdToken(std::string file_name, int line_number, int column_number, std::string text) : 
        Token(file_name, line_number, column_number, TokenType::IDENTIFIER), id(text) {}

    std::string getText() const
    {
        return id;
    }

private:
    std::string id;
};

#endif
