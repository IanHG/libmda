#include<iostream>
using std::cout;
using std::endl;
#include "../../testing/test_suite.h"
using libmda::testing::test_suite;
#include "expression_test.h"
using namespace libmda::tests::expression;
#include "../../testing/index_test_check.h"
using libmda::testing::index_test_check;
#include "../../arrays/SDArray2D.h"
using midas::mmv::SDArray2D;
#include "../../arrays/SDArray1D.h"
using midas::mmv::SDArray1D;
#include "../../arrays/MultiDimArray.h"
using libmda::MDA;
#include "matrix_test_case.h"
using libmda::tests::expression::matrix_test_case;
using libmda::tests::expression::total_test_case;

#include "../../util/has_member.h"
using libmda::util::has_vec_at;
using libmda::util::has_assignable_vec_at;

/* declare d_matrix to use index_test_check, 
   which can throw a test_failed exception */
typedef SDArray2D<double,std::allocator<double>,index_test_check> d_matrix;
typedef SDArray1D<double,std::allocator<double>,index_test_check> d_vector;

typedef MDA<double,2> mda_matrix;

template<bool>
void matrix_assign(d_matrix&);

template<>
void matrix_assign<true>(d_matrix& mat)
{ 
   for(int i=0; i<mat.size(); ++i) 
      mat.vec_at(i) = 1.0; 
}

template<>
void matrix_assign<false>(d_matrix& mat)
{ 
   for(int i=0; i<mat.extent<0>(); ++i)
      for(int j=0; j<mat.extent<1>(); ++j)
         mat.at(i,j) = 1.0;
}

int main()
{
   test_suite suite;
   
   //suite.add_test<matrix_test_case<d_matrix> >();
   //suite.add_test<matrix_test_case<mda_matrix> >();
   
   suite.add_test<total_test_case<d_matrix,d_vector> >();
   //suite.add_test<vec_char_expr_expr_test<d_vector> >();
   
   //d_matrix mat(2,2);
   //matrix_assign<has_assignable_vec_at<d_matrix>::value>(mat);
   //cout << mat << endl;
   suite.do_tests();

   return 0;
}
