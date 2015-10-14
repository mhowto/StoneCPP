#ifndef __STONE_PARSER_H
#define __STONE_PARSER_H

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <boost/variant.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "ast/name.h"
#include "ast/string_literal.h"
#include "ast/number_literal.h"
#include "ast/operators.h"
#include "ast/unary_operation.h"
#include "ast/binary_operation.h"
#include "ast/ast_tree.h"

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


typedef boost::variant <
    boost::recursive_wrapper<StringLiteral>,
    boost::recursive_wrapper<NumberLiteral>,
    boost::recursive_wrapper<Name>,
    boost::recursive_wrapper<UnaryOperation>,
    boost::recursive_wrapper<BinaryOperation>
> expression_type;

typedef boost::variant <
    Name,
    StringLiteral,
    NumberLiteral
> primary_type;


//BOOST_FUSION_ADAPT_STRUCT(BinaryOperation, (BinaryOperator, op), (std::vector<ASTree*>, children))
template <typename Iterator, typename Lexer>
struct StoneGrammar
    : qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{
        template <typename TokenDef>
    StoneGrammar(TokenDef const& tok)
        : StoneGrammar::base_type(program)
    {
//        using namespace qi::labels;

        andOp.add
            ("&", BinaryOperator::AND)
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

        program
            = -statement >> (qi::lit(';') | '\n')
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
            = expression
            ;

        block
            = '{' >> -statement >> *((qi::lit(';') | '\n') >> -statement) >> '}'
            ;

        /*
        expression
            = factor >> *(op >> factor)
            ;
        */

        expression
            = '(' >>  expression >> ')'
            | equal
            //| value
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

        /*
        factor
            = '-' >> primary
            | primary
            ;

        op
            = qi::lit('+')
            | '-'
            | '*'
            | '/'
            | qi::lit('=')
            | qi::lit("||")
            ;
        */

        primary
            //= '(' >> expression >> ')'
            = tok.identifier[qi::_val = phx::new_<Name>(qi::_1)]
           // | tok.identifier[std::cout << labels::_1 << std::endl]
            | tok.number[qi::_val = phx::new_<NumberLiteral>(qi::_1)]
            //| tok.number[std::cout << labels::_1 << std::endl]
            | tok.string_literal[qi::_val = phx::new_<StringLiteral>(qi::_1)]
            //| tok.string_literal[std::cout <<labels::_1 << std::endl]
            ;
    }

    //typedef boost::variant<unsigned int, std::string> expression_type;

    qi::rule<Iterator, qi::in_state_skipper<Lexer> > program, block, statement;
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > assignment, if_stmt;
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > while_stmt;
    qi::rule<Iterator, qi::in_state_skipper<Lexer> > simple_stmt;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, ASTree*() > value;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type*() > primary;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, ASTree*() > primary;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type() > equal, lowerGreater, shift, addSub, multDivMod;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type*() > equal, lowerGreater, shift, addSub, multDivMod;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, ASTree*() > equal, lowerGreater, shift, addSub, multDivMod;
    qi::symbols<char, BinaryOperator> commaOp, assignOp, orOp, andOp, bitwiseOrOp,bitwiseXorOp, bitwiseAndOp, equalOp,
                                    lowerGreaterOp, shiftOp, addSubOp, multDivModOp;

    //  the expression is the only rule having a return value
    //qi::rule<Iterator, expression_type(), qi::in_state_skipper<Lexer> >  expression;
    //qi::rule<Iterator, qi::in_state_skipper<Lexer>, expression_type*() > expression;
    qi::rule<Iterator, qi::in_state_skipper<Lexer>, ASTree*() > expression;
};

#endif
