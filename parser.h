#ifndef parser_H
#define parser_H
#include <vector>
#include <string>

class Parser {
	public:
		static bool isNumeric(std::string&);
		static void parse(std::string&, char&);

		const static std::string typeStrs[];
		enum TokenType {Pow, Mult, Div, Add, Sub, LParen, RParen, Num, Var, Udef};
		struct Token;
		struct Node;

	private:
		static void tokenize(std::string&, char&, std::vector<Token>&);
		static void verbosifyTokens(std::vector<Token>&, std::vector<Token>&);

		static Node buildTree(std::vector<Token>&);
		static Node* simplifyTree(std::vector<Node*>&, int);
};

#endif
