#include "parser.h"
#include <string>

int main(){
	std::string eq = "4x^2 + 10 x + 3 (5 )";
	char var = 'x';
	Parser::parse(eq, var);
	return 0;
}
