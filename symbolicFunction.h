#pragma once
#ifndef symbolicFunction_H
#define symbolicFunction_H
#include <math.h>
#include <vector>
#include <string>

//X_P - presition of the domain
//Y_P - presition of the range
template <class X_P, class Y_P>
class symbolicFunction
{
private:

public:
	symbolicFunction(Y_P (*func)(X_P, std::vector<double>), std::vector<double> &constants){
		printf("%d\n", (*func)(10, constants));
	}
};

#endif
