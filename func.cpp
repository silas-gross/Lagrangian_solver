#include "func.h"

std::vector<Functions::point_function> Functions::convert_to_point(Functions::symbolic_function* sfunc, int dim)
{
	//faster to just pass dim than referncce the class member all the time
	std::vector<point_function> pfuncs(dim);
	
	for (int i = 0; i < dim; i++)
	{
		point_function* pf = new *point_function
		pf->input_label = sfunc->vlist(i);
		pf->degree_of_deriv = sfunc->v_deriv(i);
		pf->dop = sfunc.each_var_is_poly.at(i);
		pf->string_expression = symbolic_function::strip_string_expression(sfunc.string_expression, pf->input_label);
		pfuncs.at(i) = *pf;

	}

}
void Functions::symbolic_function::fill_values(std::string express, int dim)
{
	if (dim == 1)
	{
		this->is_one_d = true;
		
	}
	else
	{
		this->is_one_d = false;
		this->n_of_variables = dim;
		this->vlist.resize(dim);
		this->v_deriv.resize(dim);
		this->each_var_is_poly.reserve(dim);
		this->dimension = dim;
		this->dops.resize(dim);
		this->cod.resize(dim);
	}
}
Functions::symbolic_function::symbolic_function(std::string express, int dim)
{
	this->dimension = dim;
	this->string_expression = express;
	fill_values(express, dim);

}
