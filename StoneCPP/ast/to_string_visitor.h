#ifndef _TO_STRING_VISITOR_H
#define _TO_STRING_VISITOR_H

#include "visitor.h"
#include <sstream>
#include <algorithm>

class ToStringVisitor : public Visitor
{
private:
    std::string str_;

public:
    std::string string()
    {
        return str_;
    }

    // Inherited via Visitor
    virtual void visit(IfStatement &if_stmt) override
    {
        std::stringstream oss;
        oss << "if ";
        if_stmt.expr()->accept(*this);
        oss << this->string() << '{';
        std::vector<Statement*> if_block_ = if_stmt.if_block();
        std::for_each(if_block_.begin(), if_block_.end(),
            [&oss, this](Statement* stmt) {
            stmt->accept(*this);
            oss << this->string();
        });
        oss << '}';
        
        std::vector<Statement*> else_block_ = if_stmt.else_block();
        if (else_block_.size() != 0)
        {
            oss << "else {";
            std::for_each(else_block_.begin(), else_block_.end(),
                [&oss, this](Statement* stmt) {
                stmt->accept(*this);
                oss << this->string();
            });
            oss << '}';
        }
        str_ = oss.str();
    }

    virtual void visit(WhileStatement & while_stmt) override
    {
        std::stringstream oss;
        oss << "while ";
        while_stmt.expr()->accept(*this);
        oss << this->string() << '{';
        std::vector<Statement*> block = while_stmt.block(); 
        std::for_each(block.begin(), block.end(),
            [&oss, this](Statement* stmt) {
            stmt->accept(*this);
            oss << this->string();
        });
        oss << '}';
        str_ = oss.str();
    }

    virtual void visit(ClassDef & class_def) override
    {
        std::stringstream oss;
        oss << "class " << class_def.get_identifier() + " extends " + class_def.get_extended_identifier();
        std::vector<ClassDef::member_type> members = class_def.get_members();
        std::for_each(members.begin(), members.end(),
            [&oss, this](ClassDef::member_type member) {
            member->accept(*this);
            oss << this->string();
        });
        str_ = oss.str();
    }

    virtual void visit(FuncDef & func_def) override
    {
        std::stringstream oss;
        oss << "def " << func_def.get_identifier() << '(';
        std::vector<std::string> params = func_def.get_params();
        std::for_each(params.begin(), params.end(),
            [&oss, this](std::string param) {
            oss << param << ',';
        });
        oss << ') {';
        for (auto stmt : func_def.get_block())
        {
            stmt->accept(*this);
            oss << this->string() << ';';
        }
        oss << '}';
        str_ = oss.str();
    }

    virtual void visit(BinaryOperation& binary_operation) override
    {
        std::stringstream oss;
        binary_operation.left_expr()->accept(*this);
        oss << this->string();
        oss << binary_operation.get_op();
        binary_operation.right_expr()->accept(*this);
        oss << this->string();
        str_ = oss.str();
    }

    virtual void visit(UnaryOperation& unary_operation) override
    {
        std::stringstream oss;
        oss << unary_operation.get_op();
        unary_operation.expr()->accept(*this);
        oss << this->string();
        str_ = oss.str();
    }
};

#endif