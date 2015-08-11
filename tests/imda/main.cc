#include <iostream>
#include <typeinfo>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"

#include "../expression/matrix_test_case.h"

#include "custom_vector.h"
#include "imda_test.h"

int main()
{
   // init
   test_suite suite;
   
   //custom_vector<double> vec(2);

   // add tests
   //suite.add_test<libmda::tests::expression::vector_test_case<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_assign_test<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_assign_scalar_test<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_add_assign_scalar_test<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_sub_assign_scalar_test<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_mul_assign_scalar_test<custom_vector<double> > >();
   suite.add_test<libmda::tests::imda::vector_div_assign_scalar_test<custom_vector<double> > >();
   
   //suite.add_test<libmda::tests::imda::vector_assign_test<custom_vector<float> > >();
   //suite.add_test<libmda::tests::imda::vector_assign_scalar_test<custom_vector<float> > >();
   //suite.add_test<libmda::tests::imda::vector_add_assign_scalar_test<custom_vector<float> > >();
   //suite.add_test<libmda::tests::imda::vector_sub_assign_scalar_test<custom_vector<float> > >();
   //suite.add_test<libmda::tests::imda::vector_mul_assign_scalar_test<custom_vector<float> > >();
   //suite.add_test<libmda::tests::imda::vector_div_assign_scalar_test<custom_vector<float> > >();
   
   // run
   suite.do_tests();
   
   return 0;
}
