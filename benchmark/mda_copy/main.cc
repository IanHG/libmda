#include <iostream>

#include "mda_copy_test.h"
using namespace libmda::benchmark;

int main()
{
   test_suite suite;
    
   //suite.add_performance_test<2000000,mda_copy_test >("mda copy test");
   suite.add_performance_test<200,mda_piece_copy_test >("mda piece copy test");
    
   suite.do_tests();

   return 0;
}
