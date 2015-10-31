#include "stdafx.h"
#include "CppUnitTest.h"
#include "../StoneCPP/stone_parser.h"
#include "../StoneCPP/ast/to_string_visitor.h"


//#include <boost/spirit/include/lex_lexertl.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//using namespace boost::spirit;
//using boost::phoenix::val;

namespace StoneCPPTest
{		
    TEST_CLASS(ParserTest1)
    {
    private:
        // iterator type used to expose the underlying input stream
        typedef std::string::iterator base_iterator_type;

        typedef lex::lexertl::token<
            base_iterator_type, boost::mpl::vector<unsigned int, std::string>
        > token_type;

        typedef lex::lexertl::lexer<token_type> lexer_type;
        typedef StoneToken<lexer_type> stone_token;
        typedef stone_token::iterator_type iterator_type;
        typedef StoneGrammar<iterator_type, stone_token::lexer_def> stone_grammar;

        stone_token tokens;
        stone_grammar* parser;                      // our parser
        ToStringVisitor printer;


    public:
        TEST_METHOD_INITIALIZE(setUp)
        {
            // method initialization code
            Logger::WriteMessage("CalculatorTest setUp()\n");
            parser = new stone_grammar(tokens);
        }
        TEST_METHOD_CLEANUP(tearDown)
        {
            // test method cleanup  code
            Logger::WriteMessage("CalculatorTest tearDown()\n");
            delete parser;
        }

        TEST_METHOD(TestMethod1)
        {
            // TODO: Your test code here
            std::string str =R"(even = 0
)";
//odd = 0
//i = 1

            // At this point we generate the iterator pair used to expose the
            // tokenized input stream.
            std::string::iterator it = str.begin();
            iterator_type iter = tokens.begin(it, str.end());
            iterator_type end = tokens.end();

            AST *ast;
            ToStringVisitor printer;

            bool r = qi::phrase_parse(iter, end, *parser, qi::in_state("WS")[tokens.self], ast);

            if (r && iter == end)
            {
                std::cout << "-------------------------\n";
                std::cout << "Parsing succeeded\n";
                std::cout << "-------------------------\n";
                ast->accept(printer);
                assert("even=0", printer.string());
            }
            else
            {
                std::cout << "-------------------------\n";
                std::cout << "Parsing failed\n";
                std::cout << "-------------------------\n";
            }
        }
	};
}