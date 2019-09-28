#pragma once
#include "func.h" 

class symbolic_function : public Functions {
		std::vector<std::string> variable_names;
		std::string equation="";
		std::vector<std::string> single_dim_equations;
	public:
		void symbolic_function();
		void symbolic_function(std::string);
		void at(int);
		int get_dimension() { return dimension; };
		std::string get_equation() { return equation; };
		std::vector<std::string> get_variable_names() { return variable_names; };
		std::vector<std::string> get_single_dim_equations() { return single_dim_equations; };
	private:
		void set_dimension();
		void set_equation();
		void set_variable_names();
		void set_single_dim_equations();
		void set_seperable(); 
		//This is actually going to be very hard to do, need to include a failure case
};
