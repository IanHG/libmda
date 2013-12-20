#include <iostream>

#include "ptr_test.h"
using namespace libmda::benchmark;

int main()
{
   test_suite suite;
    
   suite.add_performance_test<20000000000,ptr_test1 >("ptr test1");
   //suite.add_performance_test<2000000000,sequence_test >("seq test1");
   //suite.add_performance_test<20000000,sequence_test2 >("seq test1");
    
   suite.do_tests();

   return 0;
}
