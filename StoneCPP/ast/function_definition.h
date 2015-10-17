#ifndef _FUNCTION_DEFITION_H
#define _FUNCTION_DEFITION_H

#include "ast.h"
#include <string>

class FuncDef : public AST
{
public:
private:
    std::string identifier;
    std::vector<std::string> params;

};

#endif