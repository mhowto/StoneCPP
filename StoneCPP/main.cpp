#include "stone_parser.h"
#include "example.h"

int main() {
    typedef std::string::iterator base_iterator_type;

    typedef lex::lexertl::token<
        base_iterator_type, boost::mpl::vector<unsigned int, std::string>
    > token_type;

    typedef lex::lexertl::lexer<token_type> lexer_type;
    typedef StoneToken<lexer_type> stone_token;
    typedef stone_token::iterator_type iterator_type;
    typedef StoneGrammar<iterator_type, stone_token::lexer_def> stone_grammar;

    stone_token tokens;
    stone_grammar parser(tokens);

    // TODO: Your test code here
    //std::string str(read_from_file("while_state.input"));
    //std::string str = "even || \"kkk\"\n";
    std::string str = "even = 3\n";
    //std::string str = "even || 0\n";
    //std::string str = "even = 0 odd =0 i =1";
    //odd = 0
	//i =1

    std::string::iterator it = str.begin();
    iterator_type iter = tokens.begin(it, str.end());
    iterator_type end = tokens.end();

    bool r = qi::phrase_parse(iter, end, parser, qi::in_state("WS")[tokens.self]);

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

    std::cout << "Bye... :-) \n\n";
    std::cin >> r;
    return 0;
}
