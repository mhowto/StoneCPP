#ifndef _CLASS_DEFINITION_H
#define _CLASS_DEFINITION_H

#include "ast.h"
#include <string>
#include <vector>

class Visitor;

class ClassDef : public AST
{
public:
    //typedef boost::variant<Expression*, FuncDef*> member_type;
    typedef AST* member_type;

    ClassDef(std::string iden) : identifier(iden) {}
    ClassDef(std::string iden, std::string ext_iden) : identifier(iden), extented_identifier(ext_iden) {}

    ~ClassDef()
    {
        for (std::vector<Statement*>::size_type  i = 0; i < members.size(); ++i)
        {
            delete members[i];
        }
    }

    std::string get_identifier()
    {
        return identifier;
    }

    std::string get_extended_identifier()
    {
        return extented_identifier;
    }

    std::vector<member_type> get_members()
    {
        return members;
    }

    virtual void accept(Visitor& visitor) override;

private:
    std::string identifier;
    std::string extented_identifier;
    std::vector<member_type> members;
};

#endif