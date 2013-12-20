#ifndef LIBMDA_TESTS_MATRIX_TEST_CASE_H
#define LIBMDA_TESTS_MATRIX_TEST_CASE_H

#include "../../testing/testing_interface.h"
#include "addition_test.h"
#include "contraction_test.h"
using namespace libmda::tests::char_expression;

namespace libmda
{
namespace tests
{

template<class matrix_type>
struct matrix_test_case: virtual public test_case
{
   matrix_test_case()
   {
      // addition/subtraction tests
      add_test<addition_test_square_mat<matrix_type> >("addition_test square matrix");
      add_test<plusequal_test_square_mat<matrix_type>>();
      add_test<minusequal_test_square_mat_trans<matrix_type> >();
      add_test<subtraction_test_square_mat<matrix_type> >();
      add_test<addition_test_square_mat_trans<matrix_type> >();
      add_test<subtraction_test_square_mat_trans<matrix_type> >();
      add_test<addition_test_mat<matrix_type> >();
      add_test<addition_test_mat_trans<matrix_type> >();
      add_test<addition_test_mat_trans_2<matrix_type> >();
      
      // contraction tests
      add_test<contraction_test_square_mat<matrix_type> >();
      add_test<contraction_test_square_mat_trans<matrix_type> >();
      add_test<contraction_test_mat<matrix_type> >();
      add_test<contraction_addition_test_square_mat<matrix_type> >();
   };
};

template<class vector_type>
struct vector_test_case: virtual public test_case
{
   vector_test_case()
   {

   }
};

template<class tensor_type>
struct tensor_test_case: virtual public test_case
{
   tensor_test_case()
   {

   }
};

template<class matrix_type, class vector_type>
struct matrix_vector_test_case: 
   virtual public test_case, 
   virtual public matrix_test_case<matrix_type>, 
   virtual public vector_test_case<vector_type>
{ 
   matrix_vector_test_case()
   {
      add_test<contraction_test_mat_vec<matrix_type,vector_type> >();
   }
};

template<class tensor_type, class matrix_type, class vector_type>
struct tens3d_matrix_vector_test_case:
   virtual public test_case,
   virtual public matrix_vector_test_case<matrix_type,vector_type>,
   virtual public tensor_test_case<tensor_type>
{
   tens3d_matrix_vector_test_case()
   {
      add_test<contraction_test_tens3d_mat_vec<tensor_type,matrix_type,vector_type> >();
   }
};

} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_MATRIX_TEST_CASE_H */
