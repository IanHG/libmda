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

   std::cout << (d + d2) << std::endl;
   
   return 0;
}
