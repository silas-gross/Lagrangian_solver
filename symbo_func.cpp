#include "symbo_func.h"
#include <sstream>

void symbolic_function::at(int)
{

}
void symbolic_function::symbolic_function() {}

void symbolic_fuction::symbolic_function(std::string a)
{
	this->equation = a;
	set_dimension();
	this->variable_names.size() = symbolic_function::get_dimension();
	symbolic_function::set_variable_names();
	this->single_dim_equations.size() = symbolic_function::get_dimension();
	symbolic_function::set_single_dim_equations();

}
void symbolic_function::set_variable_names()
{
	std::string a = this->equation;
	std::vector <std::string> variables;
	std::stringstream sep;
	while ()
	{

	}
	
}