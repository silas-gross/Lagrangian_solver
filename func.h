#pragma once
#ifndef func_H
#define func_H
#include <math.h>
#include <vector>
#include <string>
#include <map>

class Functions
{
public:
	int dimensions=2;
	std::string input;
	std::string output;
	struct point_function
	{
		int dimension;
		std::map<double, double> single_input_output;
		std::map<std::vector<double>, double> multi_input_output;
	};
	//std::vector <std::string> symbolic_function(std::string variable_label, int degree_of_deriv); //These two need to be variable types, need to figure out how to do this....
	//std::vector <double> point_function(std::vector <std::string> sym_fun); //I am thinking making it some sort of vector with attributes about what sort of thing it is, i.e. variable name, degree of derivatie, dependence.....
private:

};
#endif
