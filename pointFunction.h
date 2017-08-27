#pragma once
#ifndef pointFunction_H
#define pointFunction_H
#include <math.h>
#include <vector>
#include <string>

template <class T>
class pointFunction
{
private:

public:
	std::vector<T> values;

	//Creates a list of values of the output of a symbolic function object.
	//	symbolic - symbolic function to be evaluated
	//	min - value to start evaluating from (inclusive)
	//	max - value to finish evaluating at (inclusive)
	//	step - amount to increment domain by
	//	T - precision of the range of symbolic
	pointFunction(symbolicFunction<T> &symbolic, double min, double max, double step){
		for (double i = min; i <= max; i += step)
			values.push_back(symbolic.evaluate(i));
	}
}
