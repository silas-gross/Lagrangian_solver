// Lagrangian_solving.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "C:\Users\Silas Grossberndt\Documents\Visual Studio 2015\Projects\calc.h"
#include "..\..\func.h"
#include <iostream>
#include "TH1.h"
//add a gui wrapper. Maybe do in Mathematica or Python?
int main()
{
	Functions::symbolic_function*  lfunc=new	Functions::symbolic_function(); 
	
	std::string eomorS="";
	bool full_eom;
	std::cout << " Please enter the Largangian with v in place of the time derivative of q. For multple qs, please write as \" q1, q2...\" " << std::endl;
	std::cin >> lfunc->equation_string;
	while (eomorS == "")
	{
		std::cout << "Would you like the equations of motion (EoM), or just the Action (S)? ";
		std::cin >> eomorS;
		if (eomorS == "EOM" || eomorS == "eom" || eomorS == "EoM") full_eom = 1;
		if (eomorS == "S" || eomorS == "Action" || eomorS == "action" || eomorS == "s") full_eom = 0;
		else
		{
			std::cout << " \n I am sorry I did not understand that " << std::endl;
			eomorS = "";
		}
	}

	auto pfuncs =Functions::convert_to_point(lfunc);
	Functions::point_function qderiv = calc::derivate(pfuncs, lfunc, "q");
	Functions::point_function vtderiv = calc::derivate(calc::derivate(pfunc, lfunc, "v"), calc::derivate(pfunc, lfunc, "v").convert_to_symbolic(), "t");
	calc::find_solutions(qderiv, vtderiv);

	return 0;
}

