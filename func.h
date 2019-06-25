<<<<<<< HEAD
#pragma once
#ifndef func_H
#define func_H
#include <math.h>
#include <vector>
#include <string>

class Functions
{
public:
	std::vector <std::string> symbolic_function(std::string variable_label, int degree_of_deriv, ); //These two need to be variable types, need to figure out how to do this....
	std::vector <double> point_function(std::vector <std::string> sym_fun); //I am thinking making it some sort of vector with attributes about what sort of thing it is, i.e. variable name, degree of derivatie, dependence.....
private:

};
=======
#pragma once
#ifndef func_H
#define func_H
#endif
#include <math.h>
#include <vector>
#include <string>
#include <map>
#include <sstream>
class Functions
{
public:
	class symbolic_function //by doing this as a class I can do mor auto fill and better flexibility in later expressions. Beter memory usage.
	{
		bool is_one_d; //if true, don't use vectors
		char variable_label='x'; //allows for genericly named variable input 
		int degree_of_deriv=0; //what stage from the base equation. Usefull for doing higher power expansion. Always intialize wih =0
		int n_of_variables=1; //for multidimenional dependence 
		std::vector<std::string> vlist; //vector formed of all the variable labels
		std::vector<int> v_deriv; //degree of devs for each variable
		std::string string_expression; //string representing the equation at question, will use to label output/ generate the graph
		bool is_poly; //are all variables just a polynomial expressions
		std::vector<bool> each_var_is_poly; //stores if each variable in the set is a polynomial
		std::vector<int> dops; //degree of polynomial
		std::vector<std::vector<float>> cod; //for each degree <dop, what is the associated coeficient. Can wrtie with additional variable, needc to be careful not to double count
		int dimension; //gives the dimension of the function (length of Vlist+1)
		std::string equation_string; //gives the equation as a parable string
		std::vector<float> cod_one_var; //for 1 D access (faster)
	public:
		symbolic_function(std::string, int); //autopropagates the class type based on the input expression and given dimension. Dim from gui processing
		~symbolic_function();
		std::string strip_string_epression(std::string, char); //takes a muti-dim down to a single dimension 
	private:
		void fill_values(std::string);
		void send_to_polynomial(bool);
		
	}; 
	class point_function 
	{
		char input_label; //allows for genericly named variable input 
		int degree_of_deriv = 0; //what stage from the base equation. Usefull for doing higher power expansion. Always intialize wih =0
		std::string string_expression; //string representing the equation at question, will use to label output/ generate the graph
		bool is_poly; //is any one variable just a polynomial expression
		int dop; //degree of polynomial
		int cod; //for each degree <dop, what is the associated coeficient. Can wrtie with additional variable, needc to be careful not to double count
		double max; //defined range for the function 
		double min; //defined range for the function
		std::map <std::double_t, std::double_t> input_output_points; //this gives a point by point mapping of the input to the output. Assumes a properly defined function. (non-invtertible)
		unsigned int granularity=1; //defines how many input points to place in the range. Does as a percentage, where the 1% defines (max-min)/, 100% is (max-min)/, such that each point is evently spaced 
	public:
		point_function(std::string, int = 0, int = 100);
		~point_function();
		std::string regression(bool, std::string, float);
	private:
		void fill_values(std::string, int, int);
		void make_graph();
	}; 
	std::vector<point_function> convert_to_point(symbolic_function*, int=2); //multidemensional functions
	symbolic_function convert_to_symbol(std::vector<point_function*>); //multideminsional
	symbolic_function convert_to_symbol(point_function*); //1D
	point_function convert_to_point(symbolic_function*); //for 1D input
	bool reg_is_good(symbolic_function*, std::string); //tests if a regression is good then gives true if avarge Variance<5%
	//conditional overloads if one D???
private:
	std::map<std::double_t, std::double_t> choose_1_to_point(std::vector<std::string>, std::string); //takes 1 variable and goes from SP 
	std::string rough_convert_one_var(std::map<std::double_t, std::double_t>); //takes 1 var and makes approxs to get epression of that variable, never going to e bes, just gives linear combiniations 
	std::string strip_string_expression(std::string, std::string);
	
};
>>>>>>> Calc_and_funcs
