#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "float_eq_test.h"

int main()
{
   libmda::testing::test_suite suite;
   
   suite.add_test<libmda::numeric_test::float_eq_test >();
   suite.add_test<libmda::numeric_test::float_neq_test>();
   suite.add_test<libmda::numeric_test::float_sign_test>();
   
   suite.do_tests();

   return 0;
}
