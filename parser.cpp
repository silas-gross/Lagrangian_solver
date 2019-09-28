#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "parser.h"


// A wrapper for the token string and the type of token it is
struct Parser::Token {
	std::string value;
	TokenType type;

	std::string toString(){
		return value;
	}
};

// This could be condensed, but I wasn't really feeling it
// Its efficient enough tho
bool Parser::isNumeric(std::string &s){
	bool decimalFound = false;
	for (std::string::size_type i = 0; i < s.size(); i++){
		// Digits are always good
		if (std::isdigit(s[i]))
			continue;
		// Negatives (-) are okay if its the first character
		if (s[i] == '-' && i == 0)
			continue;

		// Deimals are okay only once
		if (s[i] == '.' && !decimalFound){
			decimalFound = true;
			continue;
		}

		// Otherwise, we got problems
		return false;
	}
	return true;
}

// Convert an equation string to a list of tokens
// Removes whitespace and combines any adjacent numerical characters into tokens
void Parser::tokenize(std::string &eq, char &var, std::vector<Token> &tokens){
	for (auto c = eq.begin(); c != eq.end(); c++){
		if (*c == ' ')
			continue;

		std::string s(1, *c);
		if (Parser::isNumeric(s)){
			if (tokens.size() == 0 || tokens.at(tokens.size()-1).type != TokenType::Num)
				tokens.push_back(Token{s, TokenType::Num});
			else
				tokens.at(tokens.size()-1).value.append(s);
		} else {
			// Otherwise, if the char is not a digit or whitespace, its a token on its own
			// Time to figure out what type
			TokenType type;

			// Variables must be handled outside of the switch because c++ is so annoying about constexprs
			if (*c == var)
				type = TokenType::Var;

			// @TODO: There's gotta be a more elegant way of doing this, maybe with a map
			// I'm too tired to check the map docs tho
			switch (*c){
				case '+': type = TokenType::Add; break;
				case '-': type = TokenType::Sub; break;
				case '*': type = TokenType::Mult; break;
				case '/': type = TokenType::Div; break;
				case '(': type = TokenType::LParen; break;
				case ')': type = TokenType::RParen; break;
				case '^': type = TokenType::Pow; break;
			}
			tokens.push_back(Token{s, type});

		}
	}
}

// Convert a few implicit things to more verbose forms.  Perform the following conversions:
//	)(  =>  )*(
//	xy  =>  x*y
//	x(  =>  x*(
//	)x  =>  )*x
// Rather than inserting into tokens, we'll add to a new list to avoid repeated O(n) insertions
// Precondition: tokens should be nonempty
void Parser::verbosifyTokens(std::vector<Token> &tokens, std::vector<Token> &verboseTokens){
	// No need to check the first token, it will get checked when we back check from the second
	verboseTokens.push_back(tokens.at(0));
	for (int c = 1; c < tokens.size(); c++){
		TokenType t1 = tokens.at(c-1).type;
		TokenType t2 = tokens.at(c).type;
		bool insertMult = false;
		// )(  => )*(
		if (t1 == TokenType::LParen && t2 == TokenType::RParen)
			insertMult = true;
		// xy  =>  x*y
		else if ((t1 == TokenType::Num && t2 == TokenType::Var) || (t1 == TokenType::Var && t2 == TokenType::Num) || (t1 == TokenType::Var && t2 == TokenType::Var))
			insertMult = true;
		// x(  =>  x*(
		else if ((t1 == TokenType::Num || t1 == TokenType::Var) && t2 == TokenType::LParen)
			insertMult = true;
		// )x  =>  )*x
		else if (t1 == TokenType::RParen && (t2 == TokenType::Num || t2 == TokenType::Var))
			insertMult = true;

		if (insertMult)
			verboseTokens.push_back(Token{"*", TokenType::Mult});
		verboseTokens.push_back(tokens.at(c));
	}
}


void Parser::parse(std::string &eq, char &var){
	// First, check the string to make sure it contains valid numbers, symbols, and variables
//	for (char &c : eq){
//		// @TODO: This will be a pretty easy thing, I just don't have wifi for any docs right now or memory of c++'s char methods
//	}

	std::vector<Token> tokens;
	Parser::tokenize(eq, var, tokens);

	std::vector<Token> vbTokens;
	Parser::verbosifyTokens(tokens, vbTokens);

	std::for_each(vbTokens.begin(), vbTokens.end(), [](Token &token){
		std::cout << token.toString() << ", ";
	});

	std::cout << std::endl;
}
