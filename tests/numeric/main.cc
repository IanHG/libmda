#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "float_eq_test.h"
#include "numeric_test.h"

int main()
{
   libmda::testing::test_suite suite;
   
   // float_eq tests
   suite.add_test<libmda::numeric_test::float_eq_test<float> >();
   suite.add_test<libmda::numeric_test::float_eq_test<double> >();
   
   suite.add_test<libmda::numeric_test::float_neq_test<double> >();
   suite.add_test<libmda::numeric_test::float_neq_test<float> >();

   suite.add_test<libmda::numeric_test::float_sign_test<double> >();
   suite.add_test<libmda::numeric_test::float_sign_test<float> >();
   
   // float_numeq tests
   suite.add_test<libmda::numeric_test::float_numeq_zero_test<double> >();
   suite.add_test<libmda::numeric_test::float_numeq_zero_test<float> >();
   
   suite.add_test<libmda::numeric_test::float_numleq_zero_test<double> >();
   suite.add_test<libmda::numeric_test::float_numleq_zero_test<float> >();
   
   suite.add_test<libmda::numeric_test::float_numgeq_zero_test<double> >();
   suite.add_test<libmda::numeric_test::float_numgeq_zero_test<float> >();
   
   // signum tests
   suite.add_test<libmda::numeric_test::signum_pos_test<double> >();
   suite.add_test<libmda::numeric_test::signum_neg_test<double> >();
   suite.add_test<libmda::numeric_test::signum_zero_test<double> >();
   suite.add_test<libmda::numeric_test::signum_pos_test<float> >();
   suite.add_test<libmda::numeric_test::signum_neg_test<float> >();
   suite.add_test<libmda::numeric_test::signum_zero_test<float> >();

   suite.do_tests();

   return 0;
}
