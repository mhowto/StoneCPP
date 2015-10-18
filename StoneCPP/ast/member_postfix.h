#ifndef _MEMBER_POSTFIX_H
#define _MEMBER_POSTFIX_H

#include "postfix.h"

class Expression;

class MemberPostfix : public Postfix
{
public:
    MemberPostfix() = default;
    MemberPostfix(IdentifierLiteral* iden): identifier(iden) {}

    ~MemberPostfix()
    {
        delete identifier;
    }

    IdentifierLiteral* get_identifier()
    {
        return identifier;
    }
    virtual void accept(Visitor& visitor) override;

private:
    IdentifierLiteral* identifier;
};

#endif
