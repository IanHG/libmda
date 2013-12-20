#include<iostream>
using std::cout;
using std::endl;
#include "../../testing/test_suite.h"
using libmda::testing::test_suite;
#include "../../testing/index_test_check.h"
using libmda::testing::index_test_check;
#include "../../arrays/SDArray2D.h"
using midas::mmv::SDArray2D;
#include "../../arrays/SDArray1D.h"
using midas::mmv::SDArray1D;
#include "../../arrays/MultiDimArray.h"
using libmda::MDA;
#include "general_test.h"
using namespace libmda::tests::general;

/* declare d_matrix to use index_test_check, 
   which can throw a test_failed exception */
typedef SDArray2D<double,std::allocator<double>,index_test_check> d_matrix;
typedef SDArray1D<double,std::allocator<double>,index_test_check> d_vector;

typedef MDA<double,2> mda_matrix;

int main()
{
   test_suite suite;
   
   suite.add_test<vector_construction_test<d_vector> >("test",2);
   suite.add_test<vector_copy_construction_test<d_vector> >("test");
   suite.add_test<vector_implicit_copy_construction_test<d_vector> >("test");
   suite.add_test<vector_copy_assignment_test<d_vector> >("test");
   
   suite.add_test<matrix_construction_test<d_matrix> >("test",2,3);
   suite.add_test<matrix_copy_construction_test<d_matrix> >("test");
   suite.add_test<matrix_implicit_copy_construction_test<d_matrix> >("test");
   suite.add_test<matrix_copy_assignment_test<d_matrix> >("test");
   
   suite.do_tests();
   return 0;
}
