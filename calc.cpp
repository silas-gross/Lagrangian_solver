#include "calc.h"
/*This class is inteded to use numerical methods to give a functional definintion of the derivatives and integrals
current issues...storing the fuctions as vectors of floats, how does one properly then use float indecies?...
this might be where the function template would be usefull, create some sort of large vector that allows for a float to be called, 
then interally convereted to a proper bound (maybe just convert it??) [2^32 limits to 1/2 floationg point precision, and that is a slow vector] 
[speed this up somehow??]
Also this will be great for plotting....now how do we do the symbolic calculus?...maybe fitting methods??..Special deriv guesses??...
UI problem, java or python's job*/

std::vector<double> calc::derivate(Functions::point_function pfunc, Functions::symbolic_function sfunc, std::string var, float boundl, float boundu){
	Functions::point_function result;
	double step = (boundu - boundl) / 100000;

	vector<float> result[100000];
	for (int i = 0; i < 100000; i++)
		result.at(i) = localdev(pfunc, sfunc, init, boundl+i, boundl+i+10100)

	return result;
}

Functions::symbolic_function find_solutions(Functions::symbolic_function func_1, Functions::symbolic_function func_2, std::string var1, std::string var2, int degree){
	std::string dev_var2=calc::set_as_derivative(var1, var2, degree);
	func_1.replace_var(var2, dev_var2);
	func_2.replace_var(var2, dev_var2);

}

std::vector<float> calc::integral(vector<float> func, bool imp, float bl, float bu){
	vector<float> result [100000]
	if (imp) {
		for (int i = 0; i < result.length(); i++) {
			result.at(i) = Reimansum(func, bl, bl + i / 100000, 100000);
			if (bl + i / 100000 >= bu) continue;
		}
	} else {
		result.at(0) = Reimansum(func, bl, bu, 1000000);
		result.pop_back()
	}
	return result;
}

//@TODO: I don't understand the mathematical equivalent of this function.  What is the goal?
double calc::localdev(Functions::point_function pfunc, Functions::symbolic_function sfunc, vector<float> init, float boundl, float boundu){
	std::vector <double> result[15000];
	float val1 = init.at(boundl);
	float val2 = init.at(boundu);
	float delta = boundu - boundl;
	float step = delta / 10001
	for (int i = 0; i < 10000; i++)
		result.at(i) = (val1 - init.at(boundu - i*step)) / (delta - i*step);

//	bool smaller;
//	if ((result.at(9999) - result.at(9998)) < (result.at(990) - result.at(989)) smaller = true;
//	else smaller = false;
	bool smaller = result.at(9999) - result.at(9998) < result.at(990) - result.at(989);

	bool approach;
	double dev = result.at(9999);

	// @TODO: I'm not sure what's going on here
	if (for (int i = 1; i < 9999; i++) { result.at(i) - dev < result.at(i - 1) - dev })approach==true;

//	if (smaller == true && approach== true) return result.at(9999);
//	else return 0;
	return smaller && approach ? result.at(9999) : 0;
}

float calc::Reimansum(vector<float> init, float boundl, float boundu, long nsteps){
	float intval = 0;
	float step = (boundu - boundl) / nsteps; //sets step size, so it needs bounds in, how am I going to figure out
	for (int i = 0; i < nsteps; i++){
		float twmiddle = init.at(boundl) + init.at(boundl + i*step); //uses middle approx, should I change this to be the trapazoid method? 
		intval+=twmiddle/2*nsteps
	}
	return intval;
}

Functions::symbolic_function calc::set_as_derivatives(std::string vel, std::string pos, int degree){
	Functions::symbolic_function deriv = (pos, degree);
	Functions::symbolic_function vel = (vel, 1);

	return deriv;
}
