#include "../../testing/testing_interface.h"
#include "tuple_test.h"
#include "index_list_test.h"

int main()
{
   test_suite suite;
   
   suite.add_test<libmda::meta_test::tuple_empty_test>();
   suite.add_test<libmda::meta_test::tuple_catenation_test>();
   suite.add_test<libmda::meta_test::tuple_at_test>();
   suite.add_test<libmda::meta_test::tuple_size_test>();
   suite.add_test<libmda::meta_test::tuple_find_test>();
   
   suite.add_test<libmda::meta_test::index_list_empty_test>();
   suite.add_test<libmda::meta_test::index_list_catenation_test>();
   suite.add_test<libmda::meta_test::index_list_size_test>();

   suite.do_tests();

   return 0;
}
