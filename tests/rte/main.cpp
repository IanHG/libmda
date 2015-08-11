#include<iostream>
#include "../../testing/testing_interface.h"
#include "../../testing/test_suite.h"
#include "rte_test.h"

int main()
{
   libmda::testing::test_suite suite;
   
   suite.add_test<libmda::rte_test::actual_rte_test>("wahtever");

   suite.do_tests();

   return 0;
}
