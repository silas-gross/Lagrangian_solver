#pragma once
#ifndef func_H
#define func_H
#include <math.h>
#include <vector>
#include <string>

template <class X, class Y>
class Functions
{
public:
	//These two need to be variable types, need to figure out how to do this....
	std::vector <std::string> symbolic_function(std::string variable_label, int degree_of_deriv, X x, Y y);

	//I am thinking making it some sort of vector with attributes about what sort of thing it is,
	//i.e. variable name, degree of derivatie, dependence.....
	std::vector <double> point_function(std::vector <std::string> sym_fun);

private:
};

#endif
