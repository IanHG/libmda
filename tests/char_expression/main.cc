#include "../../testing/test_suite.h"
#include "addition_test.h"
#include "contraction_test.h"
#include "../../testing/index_test_check.h"
#include "../../arrays/SDArray2D.h"
#include "../../arrays/SDArray1D.h"
#include "../../arrays/MultiDimArray.h"
#include "matrix_test_case.h"
using libmda::tests::matrix_test_case;
using libmda::tests::matrix_vector_test_case;
using libmda::tests::tens3d_matrix_vector_test_case;

using libmda::testing::test_suite;
using namespace libmda::tests::char_expression;
using libmda::testing::index_test_check;
using midas::mmv::SDArray2D;
using midas::mmv::SDArray1D;
using libmda::MDA;

/* declare d_matrix to use index_test_check, 
   which can throw a test_failed exception */
typedef SDArray2D<double,std::allocator<double>,index_test_check> d_matrix;
typedef SDArray1D<double,std::allocator<double>,index_test_check> d_vector;

typedef MDA<double,3> mda_tensor;
typedef MDA<double,2> mda_matrix;
typedef MDA<double,1> mda_vector;

int main()
{
   test_suite suite;
   
   suite.add_test<matrix_test_case<d_matrix> >("test case d_matrix");
   suite.add_test<matrix_test_case<mda_matrix> >("test case mda_matrix");
   
   suite.add_test<tens3d_matrix_vector_test_case<mda_tensor,mda_matrix,mda_vector> >("test case mda_matrix");
   suite.add_test<matrix_vector_test_case<d_matrix,d_vector> >("test case d_matrix d_vector");
   
   // intertype test
   suite.add_test<matrix_vector_test_case<mda_matrix,d_vector> >("test case d_matrix d_vector");

   /* square addition/subtraction tests */
   //suite.add_test<addition_test_square_mat<d_matrix> >();
   //suite.add_test<subtraction_test_square_mat<d_matrix> >();
   //suite.add_test<addition_test_square_mat_trans<d_matrix> >();
   //suite.add_test<subtraction_test_square_mat_trans<d_matrix> >();
   
   /* square plus/minus-equal tests */
   //suite.add_test<plusequal_test_square_mat<d_matrix> >();
   //suite.add_test<minusequal_test_square_mat_trans<d_matrix> >();
   
   /* non-square addition/subtraction tests */
   //suite.add_test<addition_test_mat<d_matrix> >();
   //suite.add_test<addition_test_mat_trans<d_matrix> >();
   //suite.add_test<addition_test_mat_trans_2<d_matrix> >();
   
   /* square contraction tests */
   //suite.add_test<contraction_test_square_mat<d_matrix> >();
   //suite.add_test<contraction_test_square_mat_trans<d_matrix> >();

   /* non-square contraction tests */
   //suite.add_test<contraction_test_mat<d_matrix> >();
   //suite.add_test<contraction_addition_test_square_mat<d_matrix> >();
   
   /* mat-vec contraction tests */
   //suite.add_test<contraction_test_mat_vec<d_matrix,d_vector> >();
   
   
   /* MDA MATRIX TEST */
   //suite.add_test<addition_test_square_mat<mda_matrix> >();
   //suite.add_test<subtraction_test_square_mat<mda_matrix> >();
   //suite.add_test<addition_test_square_mat_trans<mda_matrix> >();
   //suite.add_test<subtraction_test_square_mat_trans<mda_matrix> >();
   
   /* square plus/minus-equal tests */
   //suite.add_test<plusequal_test_square_mat<mda_matrix> >();
   //suite.add_test<minusequal_test_square_mat_trans<mda_matrix> >();
   
   /* non-square addition/subtraction tests */
   //suite.add_test<addition_test_mat<mda_matrix> >();
   //suite.add_test<addition_test_mat_trans<mda_matrix> >();
   //suite.add_test<addition_test_mat_trans_2<mda_matrix> >();
   
   /* square contraction tests */
   //suite.add_test<contraction_test_square_mat<mda_matrix> >();
   //suite.add_test<contraction_test_square_mat_trans<mda_matrix> >();

   /* non-square contraction tests */
   //suite.add_test<contraction_test_mat<mda_matrix> >();
   //suite.add_test<contraction_addition_test_square_mat<mda_matrix> >();
   
   /* tens-mat-vec contraction tests */
   //suite.add_test<contraction_test_mat_vec<mda_matrix,mda_vector> >();
   //suite.add_test<contraction_test_3dtens_mat_vec<mda_tensor,mda_matrix,mda_vector> >();
   
   /**** BELOW WILL FAIL BECAUSE mda_matrix AND d_vector hAVE DIFFERENT size_type's */
   /**** THIS WILL NO LONGER FAIL ! **/
   //suite.add_test<contraction_test_mat_vec<mda_matrix,d_vector> >();
   
   suite.do_tests();
   return 0;
}
