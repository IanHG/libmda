#include <iostream>
#include <typeinfo>
//#include "../../testing/testing_interface.h"
//#include "../../testing/test_suite.h"
#include "../../new_expr/scalar_expression.h"
#include "../../new_expr/binary_expression.h"
#include "../../new_expr/scalar_binary_functors.h"

using namespace libmda::expr;

int main()
{
   double d = 3.0;
   double d2 = 4.0;
   scalar_reference<double> scal_ref(d);
   scalar_reference<const double> scal_ref2(d2);
   
   std::cout << binary_expression<scalar_reference<double>
                   , scalar_reference<const double>
                   , scalar_plus<scalar_reference<double>, scalar_reference<const double> >
                   >(scal_ref,scal_ref2,scalar_plus<scalar_reference<double>, scalar_reference<const double> >())()
            << std::endl;
   
   return 0;
}
