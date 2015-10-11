#include "stdafx.h"
#include "CppUnitTest.h"
#include "stone_parser.h"

#include <cstdio>

//#include <boost/spirit/include/lex_lexertl.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace boost::spirit;
using boost::phoenix::val;

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
        //]
        // Here we use the lexertl based lexer engine.
        typedef lex::lexertl::lexer<token_type> lexer_type;

        // This is the token definition type (derived from the given lexer type).
        typedef StoneToken<lexer_type> stone_token;

        // this is the iterator type exposed by the lexer 
        typedef stone_token::iterator_type iterator_type;

        // this is the type of the grammar to parse
        typedef StoneGrammar<iterator_type, stone_token::lexer_def> stone_grammar;

        // now we use the types defined above to create the lexer and grammar
        // object instances needed to invoke the parsing process
        stone_token tokens;                         // Our lexer
        stone_grammar* parser;                      // our parser
        // (tokens);

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

            // Parsing is done based on the token stream, not the character 
            // stream read from the input.
            // Note how we use the lexer defined above as the skip parser. It must
            // be explicitly wrapped inside a state directive, switching the lexer 
            // state for the duration of skipping whitespace.
            bool r = qi::phrase_parse(iter, end, *parser, qi::in_state("WS")[tokens.self]);
            char result[100];
            std::sprintf(result, "Parse Result: %d", r);
            Logger::WriteMessage(result);

            if (r && iter == end)
            {
                std::cout << "-------------------------\n";
                std::cout << "Parsing succeeded\n";
                std::cout << "-------------------------\n";
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