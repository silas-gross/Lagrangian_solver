#ifndef parser_H
#define parser_H
#include <vector>
#include <string>

class Parser {
	public:
		static bool isNumeric(std::string&);
		static void parse(std::string&, char&);

		const static std::string typeStrs[];
		enum TokenType {Num, Var, Add, Sub, Mult, Div, LParen, RParen, Pow};
		struct Token;

	private:
		static void tokenize(std::string&, char&, std::vector<Token>&);
		static void verbosifyTokens(std::vector<Token>&, std::vector<Token>&);
};

#endif
