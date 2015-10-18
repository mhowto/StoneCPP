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

    virtual void visit(SimpleStatement &simple_stmt) override
    {
        std::stringstream oss;
        simple_stmt.get_expr()->accept(*this);
        oss << this->string();
        std::vector<Expression*> args = simple_stmt.get_args();
        if (args.size() > 0)
        {
            args[0]->accept(*this);
            oss << this->string();
            for (int i = 1; i < args.size(); ++i)
            {
                oss << ',';
                args[i]->accept(*this);
                oss << this->string();
            }
        }
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
        unary_operation.get_expr()->accept(*this);
        oss << this->string();
        str_ = oss.str();
    }

    // Inherited via Visitor
    virtual void visit(ArrayPostfix& array_postfix) override
    {
        std::stringstream oss;
        oss << '[';
        array_postfix.get_expr()->accept(*this);
        oss << this->string();
        oss << ']';
        str_ = oss.str();
    }

    virtual void visit(CallPostfix & call_postfix) override
    {
        std::stringstream oss;
        oss << '(';
        std::vector<Expression*> args = call_postfix.get_args();
        if (args.size() > 0)
        {
            args[0]->accept(*this);
            oss << this->string();
            for (int i = 1; i < args.size(); ++i)
            {
                oss << ',';
                args[i]->accept(*this);
                oss << this->string();
            }
        }
        oss << ')';
        str_ = oss.str();
    }

    virtual void visit(MemberPostfix & member_postfix) override
    {
        std::stringstream oss;
        oss << '.';
        member_postfix.get_identifier()->accept(*this);
        oss << this->string();
        str_ = oss.str();
    }

    virtual void visit(CallExpression & expr) override
    {
        std::stringstream oss;

        oss << '(';
        expr.get_expr()->accept(*this);
        oss << this->string();
        oss << ')';

        std::vector<Postfix*> postfixs = expr.get_postfixs();
        for (auto postfix : postfixs)
        {
            postfix->accept(*this);
            oss << this->string();
        }

        str_ = oss.str();
    }

    virtual void visit(ArrayLiteral & array_literal) override
    {
        std::stringstream oss;
        oss << '[';
        std::vector<Expression*> elements = array_literal.get_elements();
        if (elements.size() > 0)
        {
            elements[0]->accept(*this);
            oss << this->string();
            for (int i = 1; i < elements.size(); ++i)
            {
                oss << ',';
                elements[i]->accept(*this);
                oss << this->string();
            }
        }
        
        oss << ']';
        str_ = oss.str();
    }

    virtual void visit(StringLiteral & string_literal) override
    {
        str_ = string_literal.value();
    }

    virtual void visit(NumberLiteral & number_literal) override
    {
        std::stringstream oss;
        oss << number_literal.value();
        str_ = oss.str();
    }

    virtual void visit(IdentifierLiteral & iden) override
    {
        std::stringstream oss;

        oss << iden.value();

        std::vector<Postfix*> postfixs = iden.get_postfixs();
        for (auto postfix : postfixs)
        {
            postfix->accept(*this);
            oss << this->string();
        }

        str_ = oss.str();
    }

    virtual void visit(Block & block) override
    {
        std::stringstream oss;
        oss << '{';
        std::vector<Statement*> stmts = block.get_statements();
        if (stmts.size() > 0)
        {
            stmts[0]->accept(*this);
            oss << this->string();

            for (int i = 1; i < stmts.size(); ++i)
            {
                stmts[i]->accept(*this);
                oss << ';' << this->string();
            }
        }
        oss << '}';
        str_ = oss.str();
    }
};

#endif