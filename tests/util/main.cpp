#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "util_test.h"
#include "from_string_test.h"
#include "scope_guard_test.h"
#include "expected_test.h"


int main()
{
   libmda::testing::test_suite suite("util test suite");;
   
   ///////////////////////////////////////////////////////////////////////
   // numeric
   ///////////////////////////////////////////////////////////////////////
   // pow test
   suite.add_test<libmda::tests::util::pow_test<float> >("pow float");
   suite.add_test<libmda::tests::util::pow_test<double> >("pow double");
   
   ///////////////////////////////////////////////////////////////////////
   // from string test
   ///////////////////////////////////////////////////////////////////////
   // floating point
   suite.add_test<libmda::tests::util::from_string_float_test<float> >();
   suite.add_test<libmda::tests::util::from_string_float_test<double> >();
   //suite.add_test<libmda::tests::util::from_string_float_test<long double> >();
   
   // integral
   //suite.add_test<libmda::tests::util::from_string_int_test<short> >();
   suite.add_test<libmda::tests::util::from_string_int_test<int> >();
   suite.add_test<libmda::tests::util::from_string_int_test<long> >();
   suite.add_test<libmda::tests::util::from_string_int_test<long long> >();
   
   //suite.add_test<libmda::tests::util::from_string_int_test<unsigned short> >();
   suite.add_test<libmda::tests::util::from_string_int_test<unsigned> >();
   suite.add_test<libmda::tests::util::from_string_int_test<unsigned long> >();
   suite.add_test<libmda::tests::util::from_string_int_test<unsigned long long> >();
   
   // signed integral
   //suite.add_test<libmda::tests::util::from_string_signed_int_test<short> >();
   suite.add_test<libmda::tests::util::from_string_signed_int_test<int> >();
   suite.add_test<libmda::tests::util::from_string_signed_int_test<long> >();
   suite.add_test<libmda::tests::util::from_string_signed_int_test<long long> >();
   
   ///////////////////////////////////////////////////////////////////////
   // scope_guard test
   ///////////////////////////////////////////////////////////////////////
   suite.add_test<libmda::tests::util::scope_guard_run_test>("scope guard run");
   suite.add_test<libmda::tests::util::scope_guard_dismiss_test>("scope guard dismiss");
   
   ///////////////////////////////////////////////////////////////////////
   // expected test
   ///////////////////////////////////////////////////////////////////////
   suite.add_test<libmda::tests::util::expected_no_except_test>("expected no exception");
   suite.add_test<libmda::tests::util::expected_except_test>("expected exception");

   suite.do_tests();

   return 0;
}
