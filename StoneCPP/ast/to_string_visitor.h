#ifndef _TO_STRING_VISITOR_H
#define _TO_STRING_VISITOR_H

#include "visitor.h"
#include <string>

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
    virtual void visit(IfStatement &if_stmt) override;

    virtual void visit(WhileStatement & while_stmt) override;
  
    virtual void visit(SimpleStatement &simple_stmt) override;
   
    virtual void visit(ClassDef & class_def) override;
   
    virtual void visit(FuncDef & func_def) override;

    virtual void visit(BinaryOperation& binary_operation) override;
  
    virtual void visit(UnaryOperation& unary_operation) override;
   
    virtual void visit(ArrayPostfix& array_postfix) override;
  
    virtual void visit(CallPostfix & call_postfix) override;
    
    virtual void visit(MemberPostfix & member_postfix) override;
   
    virtual void visit(CallExpression & expr) override;
   
    virtual void visit(ArrayLiteral & array_literal) override;

    virtual void visit(StringLiteral & string_literal) override;

    virtual void visit(NumberLiteral & number_literal) override;

    virtual void visit(IdentifierLiteral & iden) override;

    virtual void visit(Block & block) override;
};

#endif