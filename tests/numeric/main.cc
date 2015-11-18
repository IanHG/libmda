#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "float_eq_test.h"
#include "numeric_test.h"

int main()
{
   libmda::testing::test_suite suite("numeric test suite");
   
   // float_eq tests
   suite.add_test<libmda::numeric_test::float_eq_test<float> >("float_eq float");
   suite.add_test<libmda::numeric_test::float_eq_test<double> >("float_eq double");
   suite.add_test<libmda::numeric_test::float_eq_test<long double> >("float_eq long double");
   
   suite.add_test<libmda::numeric_test::float_neq_test<float> >("float_neq float");
   suite.add_test<libmda::numeric_test::float_neq_test<double> >("float_neq double");
   suite.add_test<libmda::numeric_test::float_neq_test<long double> >("float_neq long double");

   suite.add_test<libmda::numeric_test::float_sign_test<float> >("float_sign float");
   suite.add_test<libmda::numeric_test::float_sign_test<double> >("float_sign double");
   suite.add_test<libmda::numeric_test::float_sign_test<long double> >("float_sign long double");
   
   // float_numeq tests
   suite.add_test<libmda::numeric_test::float_numeq_zero_test<float> >("float_numeq_zero float");
   suite.add_test<libmda::numeric_test::float_numeq_zero_test<double> >("float_numeq_zero double");
   suite.add_test<libmda::numeric_test::float_numeq_zero_test<long double> >("float_numeq_zero long double");
   
   suite.add_test<libmda::numeric_test::float_numleq_zero_test<float> >("float_numleq_zero float");
   suite.add_test<libmda::numeric_test::float_numleq_zero_test<double> >("float_numleq_zero double");
   suite.add_test<libmda::numeric_test::float_numleq_zero_test<long double> >("float_numleq_zero long double");
   
   suite.add_test<libmda::numeric_test::float_numgeq_zero_test<float> >("float_numgeq_zero float");
   suite.add_test<libmda::numeric_test::float_numgeq_zero_test<double> >("float_numgeq_zero double");
   suite.add_test<libmda::numeric_test::float_numgeq_zero_test<long double> >("float_numgeq_zero long double");
   
   // signum tests
   suite.add_test<libmda::numeric_test::signum_pos_test<float> >("signum_pos float");
   suite.add_test<libmda::numeric_test::signum_neg_test<float> >("signum_neg float");
   suite.add_test<libmda::numeric_test::signum_zero_test<float> >("signum_zero float");
   suite.add_test<libmda::numeric_test::signum_pos_test<double> >("signum_pos double");
   suite.add_test<libmda::numeric_test::signum_neg_test<double> >("signum_neg double");
   suite.add_test<libmda::numeric_test::signum_zero_test<double> >("signum_zero double");
   suite.add_test<libmda::numeric_test::signum_pos_test<long double> >("signum_pos long double");
   suite.add_test<libmda::numeric_test::signum_neg_test<long double> >("signum_neg long double");
   suite.add_test<libmda::numeric_test::signum_zero_test<long double> >("signum_zero long double");

   suite.do_tests();

   return 0;
}
