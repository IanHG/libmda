#ifndef LIBMDA_TESTS_EXPRESSION_MATRIX_TEST_H
#define LIBMDA_TESTS_EXPRESSION_MATRIX_TEST_H

#include "../../testing/testing_interface.h"
#include "expression_test.h"

namespace libmda
{
namespace tests
{
namespace expression
{

template<class matrix_type>
struct matrix_test_case_basic: virtual public test_case
{
   matrix_test_case_basic()
   {
      add_test<addition_square_mat_test<matrix_type> >("addition_square_mat_test");
      add_test<subtraction_square_mat_test<matrix_type> >("subtraction_square_mat_test");
      add_test<plusequal_mat_test<matrix_type> >("plusequal_mat_test");
      add_test<mat_equal_scalar_test<matrix_type> >("mat_equal_scalar_test");
      add_test<mat_minusequal_scalar_test<matrix_type> >("mat_minusequal_scalar_test");
      add_test<scalar_mat_test<matrix_type> >("scalar_mat_test");
      add_test<mat_scalar_test<matrix_type> >("mat_scalar_test");
      add_test<scalar_mat_expr_test<matrix_type> >("scalar_mat_expr_test");
      add_test<mat_unary_minus_test<matrix_type> >("mat_unary_minus_test");
   }
};

template<class matrix_type>
struct matrix_test_case_advanced: virtual public test_case
{
   matrix_test_case_advanced()
   {
      add_test<multiplication_square_mat_test<matrix_type> >("multiplication_square_mat_test");
      add_test<division_square_mat_test<matrix_type> >("division_square_mat_test");
      
      add_test<cos_sin_mat_test<matrix_type> >("cos_sin_mat_test"); // uses multiplication
   }
};

template<class matrix_type>
struct matrix_test_case: matrix_test_case_basic<matrix_type>, matrix_test_case_advanced<matrix_type>
{
};

template<class vector_type>
struct vector_test_case_basic: virtual public test_case
{
   vector_test_case_basic()
   {
      add_test<vec_unary_minus_test<vector_type> >("vec_unary_minus_test");
      add_test<vec_scalar_test<vector_type> >("vec_scalar_test");
      add_test<vec_scalar_test2<vector_type> >("vec_scalar_test2");
   }
};

template<class vector_type>
struct vector_test_case: vector_test_case_basic<vector_type>
{
};

template<class matrix_type, class vector_type>
struct total_test_case: matrix_test_case<matrix_type>, vector_test_case<vector_type>
{ 
};

} // namespace expression
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_EXPRESSION_MATRIX_TEST_H */
