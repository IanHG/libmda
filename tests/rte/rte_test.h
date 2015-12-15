#ifndef LIBMDA_TESTS_NUMERIC_H_INCLUDED
#define LIBMDA_TESTS_NUMERIC_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../rte/abstract_expression.h"
#include "../../rte/rte_function.h"
#include "../../util/type_info.h"

namespace libmda
{
namespace rte_test
{

struct actual_rte_test: public virtual unit_test
{
   void do_test() 
   {
      auto func = make_rte_function(make_sum_expression(rte::make_literal_expression<long int>(2)
                                                      , rte::make_literal_expression<int>(1)
                                                      )
                                   , {"x"}
                                   );
   
      rte::sum_expression<double,float> sum2(new rte::literal_expression<double>(2.0) 
                                           , new rte::literal_expression<float>(4.0) 
                                           );
      
      std::cout << " sum : " << func.evaluate() << std::endl;
      std::cout << " sum2: " << sum2.evaluate() << std::endl;
   }
};

} /* namespace rte_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_NUMERIC_H_INCLUDED */
