#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "util_test.h"

int main()
{
   libmda::testing::test_suite suite;
   
   suite.add_test<libmda::util_test::pow_test<float> >();
   suite.add_test<libmda::util_test::pow_test<double> >();

   suite.do_tests();

   return 0;
}
