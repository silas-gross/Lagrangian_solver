#include "symbolicFunction.h"

int func(int x, std::vector<double> consts){
	return x*x;
}

int main(){
	std::vector<double> consts;
	symbolicFunction<int, int> f(func, consts);
}
