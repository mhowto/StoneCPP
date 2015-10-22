#ifndef __STONE_PARSER_H
#define __STONE_PARSER_H

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/adapt_adt.hpp>

#include <boost/variant.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "ast/include_all_ast.h"
#include "ast/visitor.h"

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phx = boost::phoenix;

template <typename Lexer>
struct StoneToken : lex::lexer<Lexer>
{
    StoneToken()
    {
        // define the tokens to match
        identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
        number = "[0-9]+";
        string_literal = R"(\"(\"|\\|\n|[^"])*\")";

        // !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
        // associate the tokens and the token set with the lexer
        this->self
            = lex::token_def<>('(') | ')' | '{' | '}' | '[' | ']'
            | '+' | '-' | '*' | '/'
            | '='
            | "==" | "<=" | ">="
            | '>' | '<' | "&&"
            | '!' | '^' | '|' | '~' | '&'
            | '%'
            | '\'' | ',' | '"' | '\n' | ';' | '.' | '_'
            ;

        //this->self += number | if_ | else_ | while_ | identifier;
        this->self += number | identifier | string_literal;

        // define the whitespace to ignore (spaces, tabs, and C-style 
        // comments)
        this->self("WS")
            = lex::token_def<>("[ \\t]+")
            | R"(\/\*[^*]*\*+([^/*][^*]*\*+)*\/)"
            | R"(\/\/[^\n]*\n)"
            ;
    }

    lex::token_def<std::string> identifier;
    lex::token_def<std::string> string_literal;
    lex::token_def<unsigned int> number;
};


/*
typedef boost::variant <
    boost::recursive_wrapper<StringLiteral>,
    boost::recursive_wrapper<NumberLiteral>,
    boost::recursive_wrapper<Name>,
    boost::recursive_wrapper<UnaryOperation>,
    boost::recursive_wrapper<BinaryOperation>
> expression_type;

typedef boost::variant <
    Name*,
    StringLiteral*,
    NumberLiteral*
> primary_type;

typedef boost::variant <
    UnaryOperation*,
    primary_type
> value_type;
*/


BOOST_FUSION_ADAPT_ADT(
    CallExpression,
    (Expression*, Expression*, obj.get_expr(), obj.set_expr(val))
    (std::vector<Postfix*>, std::vector<Postfix*> , obj.get_postfixs(), (void)()))

BOOST_FUSION_ADAPT_ADT(
    CallPostfix,
    (std::vector<Expression*>, std::vector<Expression*>, obj.get_args(), (void)()))
    

template <typename Iterator, typename Lexer>
struct StoneGrammar
    : qi::grammar<Iterator, qi::in_state_skipper<Lexer>, AST*() >
{
        template <typename TokenDef>
    StoneGrammar(TokenDef const& tok)
        : StoneGrammar::base_type(program)
    {
//        using namespace qi::labels;
        commaOp.add
            (",", BinaryOperator::COMMA)
            ;
        assignOp.add
            ("=", BinaryOperator::ASSIGN)
            ;
        orOp.add
            ("||", BinaryOperator::OR)
            ;
        andOp.add
            ("&&", BinaryOperator::AND)
            ;
        bitwiseOrOp.add
            ("|", BinaryOperator::BITWISE_OR)
            ;
        bitwiseXorOp.add
            ("^", BinaryOperator::BITWISE_XOR)
            ;
        bitwiseAndOp.add
            ("&", BinaryOperator::BITWISE_AND)
            ;
        equalOp.add
            ("==", BinaryOperator::EQUAL)
            ("!=", BinaryOperator::NOT_EQUAL)
            ;
        lowerGreaterOp.add
            ("<", BinaryOperator::LOWER)
            ("<=", BinaryOperator::LOWER_EQUAL)
            (">", BinaryOperator::GREATER)
            (">=", BinaryOperator::GREATER_EQUAL)
            ;
        shiftOp.add
            ("<<", BinaryOperator::LEFT_SHIFT)
            (">>", BinaryOperator::RIGHT_SHIFT)
            ;
        addSubOp.add
            ("+", BinaryOperator::ADD)
            ("-", BinaryOperator::SUBSTRACT)
            ;
        multDivModOp.add
            ("*", BinaryOperator::MULTIPLY)
            ("/", BinaryOperator::DIVIDE)
            ("%", BinaryOperator::MODULO)
            ;

        /* Grammar for Stone:
        primary    : "(" expr ")" | NUMBER | IDENTIFIER | STRING
        factor     : "-" primary | primary
        expr       : factor { OP factor }
        block      : "{" [ statement ] { (";" | EOL) [ statement ] } "}"
        //block      : "{" [ statement ] { (";" | EOL) [ statement ] } "}"
        simple     : expr
        statement  : "if" expr block [ "else" block ]
                   | "while" expr block
                   | simple
        //program    : [ statement ] (";" | EOL)
        program    : { statement [";"] }
        */


        /* Full spec:
         * 
         program    : [defclass | deffunc | statement] (";" | EOL)

         deffunc    : "def" IDENTIFIER param_list block
         block      : "{" [ statement ] { (";" | EOL) [ statement ] } "}"
         param_list : "(" [params] ")"
         params     : param {"," param}
         param      : IDENTIFIER

         defclass   : "class" IDENTIFIER [ "extends" IDENTIFIER ] class_body
         class_body : "{" [ member ] { ( ";" | EOL ) [ member ] } "}"
         member     : deffunc 
                    | simple


         statement  : "if" expr block [ "else" block ]
                    | "while" expr block
                    | simple
         simple     : expr [ args ]
         expr       : factor { OP factor }
         factor     : "-" primary
                    | "+" primary
                    | "!" primary
                    | primary

         primary    : ( "[" [elements] "]" 
                       |  "(" expr ")" 
                       | NUMBER 
                       | IDENTIFIER 
                       | STRING ) { postfix }
         postfix    : "." IDENTIFIER 
                    | "(" [args] ")"
                    | "[" expr "]"
         args       : expr { "," expr }
         elements   : expr { "," expr }  // ¿¼ÂÇÓëargsºÏ²¢
        */

        program
            = -(class_def | func_def | statement) >> (qi::lit(';') | '\n')
            ;

        class_def
            = qi::lit("class") >> tok.identifier >> -(qi::lit("extends") >> tok.identifier) >> class_body
            ;

        class_body
            = '{' >> -member >> *((qi::lit(';') | '\n') >> -member) >> '}'
            ;

        member
            = func_def
            | simple_stmt
            ;
            
        func_def
            = qi::lit("def") >> tok.identifier >> param_list >> block
            ;

        block
            = qi::lit('{') >> -statement >> *((qi::lit(';') | '\n') >> -statement) >> '}'
            ;

        param_list
            = '(' >> -(tok.identifier >> *(',' >> tok.identifier)) >> ')'
            ;

        statement
            = if_stmt
            | while_stmt
            | simple_stmt
            ;

        if_stmt
            = "if" >> expression >> block >> -("else" >> block)
            ;

        while_stmt
            = "while" >> expression >> block;

        simple_stmt
            = expression >> -(expression >> *(qi::lit(',') >> expression))
            ;

        expression
            = assign
            ;

        //comma, assign, or_, and_, bitwise_or, bitwise_xor, bitwise_and,
        assign = or_[qi::_val = qi::_1] >> -(assignOp >> or_)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        or_ = and_[qi::_val = qi::_1] >> -(orOp >> and_)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        and_ = bitwise_or[qi::_val = qi::_1] >> -(andOp >> bitwise_or)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        bitwise_or = bitwise_xor[qi::_val = qi::_1] >> -(bitwiseOrOp >> bitwise_xor)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        bitwise_xor = bitwise_and[qi::_val = qi::_1] >> -(bitwiseXorOp >> bitwise_and)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        bitwise_and = equal[qi::_val = qi::_1] >> -(bitwiseAndOp >> equal)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        equal
            = lowerGreater[qi::_val = qi::_1] >> -(equalOp >> lowerGreater)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        lowerGreater
            = shift[qi::_val = qi::_1] >> -(lowerGreaterOp >> shift)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;
       
        shift
            = addSub[qi::_val = qi::_1] >> -(shiftOp >> addSub)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        addSub
            = multDivMod[qi::_val = qi::_1] >> -(addSubOp >> multDivMod)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        multDivMod
            = value[qi::_val = qi::_1] >> -(multDivModOp >> value)[qi::_val = phx::new_<BinaryOperation>(qi::_1, qi::_val, qi::_2)]
            ;

        value
            = '-' >> primary[qi::_val = phx::new_<UnaryOperation>(UnaryOperator::MINUS, qi::_1)]
            | ('+' >> primary)[qi::_val = phx::new_<UnaryOperation>(UnaryOperator::PLUS, qi::_1)]
            | ('!' >> primary)[qi::_val = phx::new_<UnaryOperation>(UnaryOperator::NOT, qi::_1)]
            | (primary)
            ;

        primary
            = qi::lit('[') [qi::_val = phx::new_<ArrayLiteral>()] >> -(expression [phx::push_back(phx::at_c<0>(qi::_val), qi::_1)]>> *(qi::lit(',') >> expression [phx::push_back(phx::at_c<0>(qi::_val), qi::_1)])) >> qi::lit[']']
            | qi::lit('(') >> expression [qi::_val = phx::new_<CallExpression>(qi::_1)] >> ')' >> *(postfix [phx::push_back(phx::at_c<1>(qi::_val), qi::_1)])
            | tok.identifier[qi::_val = phx::new_<IdentifierLiteral>(qi::_1)] >> *(postfix)
            | tok.number[qi::_val = phx::new_<NumberLiteral>(qi::_1)]
            | tok.string_literal[qi::_val = phx::new_<StringLiteral>(qi::_1)]
            ;

        postfix
            = qi::lit('.') >> tok.identifier [qi::_val = phx::new_<MemberPostfix>(qi::_1)]
            | '(' >> expression [qi::_val = phx::new_<CallPostfix>(qi::_1)] >> *(',' >> expression [phx::push_back(phx::at_c<0>(qi::_val), qi::_1)]) >> ')'
            | '[' >> expression [qi::_val = phx::new_<ArrayPostfix>(qi::_1)] >> ']' 
            ;
    }

    //typedef boost::variant<unsigned int, std::string> expression_type;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, AST*() > program;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, ClassDef*() > class_def;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, FuncDef*() > func_def;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, Statement*() > statement;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, std::vector<AST*>()> class_body;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, AST*()> member;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, std::vector<std::string>()> param_list;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, Block*() > block;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer> > program, block, statement;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, BinaryOperation*() > assignment;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, IfStatement*() > if_stmt;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, WhileStatement*() > while_stmt;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, SimpleStatement*() > simple_stmt;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type() > equal, lowerGreater, shift, addSub, multDivMod;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type*() > equal, lowerGreater, shift, addSub, multDivMod;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, BinaryOperation*() > comma, assign, or_, and_, bitwise_or, bitwise_xor, bitwise_and,
        equal, lowerGreater, shift, addSub, multDivMod;
    qi::symbols<char, BinaryOperator> commaOp, assignOp, orOp, andOp, bitwiseOrOp,bitwiseXorOp, bitwiseAndOp, equalOp,
                                    lowerGreaterOp, shiftOp, addSubOp, multDivModOp;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, UnaryOperation*() > value;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, PrimaryExpression*() > primary;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, ASTree*() > primary;

    qi::rule<Iterator, qi::in_state_skipper<Lexer>, Postfix*() > postfix;

    //  the expression is the only rule having a return value
    //qi::rule<Iterator, expression_type(), qi::in_state_skipper<Lexer> >  expression;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type*() > expression;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, Expression*() > expression;
};

#endif
