#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include "parser.h"

// A wrapper for the token string and the type of token it is, as well as if it should be negated or not
// Incorperating the negation into the token makes it easier to simplify the grammar early on
struct Parser::Token {
	std::string value;
	TokenType type;
	bool negate = false;

	std::string toString(){
		if (type == TokenType::Num || type == TokenType::Var)
			return (negate ? "-" : "") + value;

		std::string types[] = {"^", "*", "/", "+", "-", "(", ")"};
		return types[type];
	}

	double numericalValue(double varVal = 0.0){
		double val = varVal;
		if (type == TokenType::Num)
			val = std::stod(value);
		return negate ? -1 * val : val;
	}
};

struct Parser::Node {
	Token token;
	Node *lChild;
	Node *rChild;

	Node(Token t, Node *l, Node *r): token(t), lChild(l), rChild(r){}

	std::string toString(){
		if (lChild == 0 || rChild == 0)
			return "{" + token.toString() + "}";
		return "[" + lChild->toString() + " " + token.toString()  + " " + rChild->toString() + "]";
	}

	bool isOpLeaf(){
		if (lChild != 0 || rChild != 0)
			return false;

		// This is kinda gross as it depends on the order of the definitions of the TokenType enum, but it works
		// @TODO: Make it less gross
		return token.type < 5;
	}

	double evaluate(double varVal){
		if (token.type == TokenType::Num || token.type == TokenType::Var)
			return token.numericalValue(varVal);

		double leftVal = lChild->evaluate(varVal);
		double rightVal = rChild->evaluate(varVal);

		switch (token.type){
			case (TokenType::Pow):
				return pow(leftVal, rightVal);
			case (TokenType::Mult):
				return leftVal * rightVal;
			case (TokenType::Div):
				return leftVal / rightVal;
			case (TokenType::Add):
				return leftVal + rightVal;
			case (TokenType::Sub):
				return leftVal - rightVal;
		}
	}
};

// This could be condensed, but I wasn't really feeling it
// Its efficient enough tho
bool Parser::isNumeric(std::string &s){
	bool decimalFound = false;
	for (auto c = s.begin(); c != s.end(); c++){
		// Digits are always good
		if (std::isdigit(*c))
			continue;

		// Deimals are okay only once
		if (*c == '.' && !decimalFound){
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
//	[+-*/]-x  => [+-*/]x_negated
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

		// If this token is a Sub, potentially negate the next token and ignore this one
		if (t2 == TokenType::Sub && (t1 == TokenType::Add || t1 == TokenType::Sub || t1 == TokenType::Mult || t1 == TokenType::Div)){
			tokens.erase(tokens.begin() + c);
			tokens.at(c).negate = true;
			c--;
		} else
			verboseTokens.push_back(tokens.at(c));

	}
}

Parser::Node Parser::buildTree(std::vector<Token> &tokens){
	// Convert the list of tokens to a list of Leaves, then recursively simplify to a tree
	std::vector<Node*> nodes;
//	std::for_each(tokens.begin(), tokens.end(), [nodes](Token &token){
//		Leaf leaf{token};
//		nodes.push_back(leaf);
//	});
	for (int c = 0; c<tokens.size(); c++){
		Node *leaf = new Node(tokens.at(c), 0, 0);
		nodes.push_back(leaf);
	}

	Node *root = simplifyTree(nodes, 0);
	return *root;
}

Parser::Node* Parser::simplifyTree(std::vector<Node*> &nodes, int level){
	std::cout << std::endl << std::string(level, ' ') << "|"  << "simplifyTree(  ";
	for (int c =0; c<nodes.size(); c++)
		std::cout << nodes.at(c)->toString() << " ";
	std::cout << "  )  (size = " << nodes.size() << ")" << std::endl;


	// Base case: If the list of nodes is only 1 item long, return this
	//		Or, if it is just LParen_Node, Node, RParen_Node, return the center node
	if (nodes.size() == 1){
		std::cout << std::string(level, ' ') << "|"  << "Base case (root reached)" << std::endl;
		return nodes.at(0);
	}

	if (nodes.size() == 3 && nodes.at(0)->token.type == TokenType::LParen && nodes.at(2)->token.type == TokenType::RParen){
		std::cout << std::string(level, ' ') << "|"  << "Base case (paren'd root reached)" << std::endl;
		return nodes.at(1);
	}

	// Otherwise, follow pemdas to simplify a Node Node Node relationship to a single node

	// First, find the deepest set of parenthesis
	int parenLevel = 0;
	int deepestLevel = 0;
	int deepestStartPos = -1;
	int deepestEndPos = -1;
	int opPos[] = {-1, -1, -1, -1, -1};
	for (int c = 0; c < nodes.size(); c++){
		if (nodes.at(c)->token.type == TokenType::LParen){
			parenLevel++;
			if (parenLevel >= deepestLevel){
				deepestLevel = parenLevel;
				deepestStartPos = c;
			}
		}

		// If this RParen is closing the deepest paren, save its position
		// Otherwise, if its just any other RParen, just decrease the level
		if (nodes.at(c)->token.type == TokenType::RParen && parenLevel == deepestLevel){
			parenLevel--;
			deepestEndPos = c;
		} else if (nodes.at(c)->token.type == TokenType::RParen)
			parenLevel--;

		// If we are at a 0 paren level and the current node is a leaf op node, record its position IF a position hasn't already been recorded (to keep the left to right order)
		if (parenLevel == 0 && nodes.at(c)->isOpLeaf() && opPos[nodes.at(c)->token.type] == -1)
			opPos[nodes.at(c)->token.type] = c;
	}

	std::cout << std::string(level, ' ') << "|"  << "Deepest level: " << deepestLevel << " start: " << deepestStartPos << " end: " << deepestEndPos << std::endl;

	// If the deepest paren level is not 0, simplify this parenthesis set to a single node recursively
	if (deepestLevel > 0){
		auto subStart = nodes.begin() + deepestStartPos;
		auto subEnd = nodes.begin() + deepestEndPos + 1;

		std::vector<Node*> subEq(subStart+1, subEnd-1);
		Node *subRoot = simplifyTree(subEq, level+1);

		nodes.erase(subStart, subEnd);
		nodes.insert(subStart, subRoot);

		std::cout << std::string(level, ' ') << "|" << "Starting simplify tree on new nodes (paren)" << std::endl;
		Node *root = simplifyTree(nodes, level+1);
		std::cout << std::string(level, ' ') << "|" << "Traced (paren)" << std::endl;
		std::cout << std::string(level, ' ') << "|"  << "Following paren back: " << root->toString() << std::endl;
		return root;
	}

	// Otherwise, search in order of emdas for other operations
	// Find the first non-negative operation index to simplify that sub equation
	// Check first opPos[0] (^), then opPos[1] (*) and opPos[2] (/) at the same time (order by lesser), then opPos[3] (+) and opPos[4] (-) at the same time (order by lesser)
	// This can probably be made a little bit more beautiful, but its quick and dirty right now
	int pos = -1;
	// Check exponents
	if (opPos[0] > 0)
		pos = opPos[0];
	// Check multiplication and division
	else if (opPos[1] > 0 && opPos[2] == -1)
		pos = opPos[1];
	else if (opPos[1] == -1 && opPos[2] > 0)
		pos = opPos[2];
	else if (opPos[1] > 0 && opPos[2] > 0)
		pos = std::min(opPos[1], opPos[2]);
	// Check addition and subtraction
	else if (opPos[3] > 0 && opPos[4] == -1)
		pos = opPos[3];
	else if (opPos[3] == -1 && opPos[4] > 0)
		pos = opPos[4];
	else if (opPos[3] > 0 && opPos[4] > 0)
		pos = std::min(opPos[3], opPos[4]);

	if (pos == -1){
		// Really shouldn't ever get to hear
		// If so, something is wrong and I don't know what yet
		std::cout << "Uh oh, recursion shouldn't get here" << std::endl;
		return NULL;
	}

	Token opToken = nodes.at(pos)->token;
	nodes.at(pos)->lChild = nodes.at(pos-1);
	nodes.at(pos)->rChild = nodes.at(pos+1);
	std::cout << std::string(level, ' ') << "|"  << "subRoot: " << nodes.at(pos)->toString() << std::endl;

	nodes.erase(nodes.begin() + pos + 1);
	nodes.erase(nodes.begin() + pos - 1);

	std::cout << std::string(level, ' ') << "|"  << "erased(  ";
	for (int c =0; c<nodes.size(); c++)
		std::cout << nodes.at(c)->toString() << " ";
	std::cout << "  )" << std::endl;

	std::cout << std::string(level, ' ') << "|" << "Starting simplify tree on new nodes (op)" << std::endl;
	Node *root = simplifyTree(nodes, level+1);
	std::cout << std::string(level, ' ') << "|" << "Traced (op)" << std::endl;
	std::cout << std::string(level, ' ') << "|"  << "Following op back: " << root->toString() << std::endl;
	return root;
}


void Parser::parse(std::string &eq, char &var){
	// First, check the string to make sure it contains valid numbers, symbols, and variables
//	for (char &c : eq){
//		// @TODO: This will be a pretty easy thing, I just don't have wifi for any docs right now or memory of c++'s char methods
//	}

	// Turn the string into a list of tokens, directly as written in the equation
	std::vector<Token> tokens;
	Parser::tokenize(eq, var, tokens);

	// Verbosify and clean the token list by adding implicit operations and cleaning up ambiguous negatives
	std::vector<Token> vbTokens;
	Parser::verbosifyTokens(tokens, vbTokens);

	std::for_each(vbTokens.begin(), vbTokens.end(), [](Token &token){
		std::cout << token.toString() << ", ";
	});

	std::cout << std::endl;

	// Start building the parse tree
	Node root = Parser::buildTree(vbTokens);
	std::cout << root.toString() << std::endl;
	std::cout << root.evaluate(4.0) << std::endl;

//	Leaf leaf0(vbTokens[0]);
//	Leaf leaf1(vbTokens[1]);
//	Leaf leaf2(vbTokens[2]);
//	Leaf leaf3(vbTokens[3]);
//	Leaf leaf4(vbTokens[4]);
//	std::vector<Node> nodes = {leaf0, leaf1, leaf2, leaf3, leaf4};
//
//	for (int c=0; c<nodes.size(); c++)
//		std::cout << nodes[c].toString();
//	std::cout << std::endl;
}
