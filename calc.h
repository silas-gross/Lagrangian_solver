#pragma once
#ifndef Calc_H
#define Calc_H
#include <math.h>
#include <string>
#include <vector>
#include "func.h"


class calc {
	public:
		Functions::point_function derivate(Functions::point_function pfunc, Functions::symbolic_function sfunc, std::string var, float boundl, float boundu);
		Functions::point_function integral(std::vector <float> func, bool imp, float bl, float bu);
		Functions::symbolic_function find_solutions(Functions::symbolic_function func_1, Functions::symbolic_function func_2, std::string var1, std::string var2, int degree);
		Functions::point_function find_solutions(Functions::point_function func_1, Functions::point_function func_2, std::string var1, std::string var2, int degree);

	private:
		double localdev(Functions::point_function pfunc, Functions::symbolic_function sfunc, std::vector<float> init, float boundl, float boundu); 
		/********************************************************************************
		*              The following describes the purpose of each parameter            *
		* Parameter 1: Point function representation of 
		* Parameter 2: Symbolic Function representation 
		* Parameter 3:
		* Parameter 4:
		* Parameter 5:
		*/
		float Reimansum(std::vector<float> init, float boundl, float boundu, long nsteps); //
		std::string set_as_derivative(std::string var1, std::string var_2, int degree) //replaces variable 1 with a derivatve of variable 2 of given degree
};

#endif	
