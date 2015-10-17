#ifndef _CLASS_DEFINITION_H
#define _CLASS_DEFINITION_H

#include "ast.h"
#include <string>
#include <vector>

#include <boost/variant.hpp>

class Expression;
class FuncDef;

class ClassDef : public AST
{
public:
    typedef boost::variant<Expression*, FuncDef*> member_type;

    ClassDef(std::string iden) : identifier(iden) {}
    ClassDef(std::string iden, std::string ext_iden) : identifier(iden), extented_identifier(ext_iden) {}

    virtual std::string toString() override
    {
        return "class" + identifier + " extends " + extented_identifier;
    }

    virtual std::string location() override
    {
        return "unknown";
    }

private:
    std::string identifier;
    std::string extented_identifier;
    std::vector<member_type> members;
};

#endif