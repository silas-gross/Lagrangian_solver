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
	class symbolic_function
	{
		int dimension=0;
		std::vector<std::string> variable_names;
		std::string equation="";
		std::vector<std::string> single_dim_equations;
	public:
		symbolic_function();
		symbolic_function(std::string);
		std::string at(int);
		int get_dimension() { return dimension; };
		std::string get_equation() { return equation; };

	private:
		void set_dimension();
		void set_equation();
		void set_variable_names();
		
		
		void set_seperable(); 
		//This is actually going to be very hard to do, need to include a failure case
	};
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
