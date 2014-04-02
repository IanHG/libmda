#ifndef LIBMDA_TESTS_CHAR_EXPRESSION_CONTRACTION_TEST_H
#define LIBMDA_TESTS_CHAR_EXPRESSION_CONTRACTION_TEST_H

#include<iostream>
using std::cout;
using std::endl;
#include "../../testing/testing_interface.h"
#include "../../expr/cindex.h"
using libmda::cindex;

namespace libmda
{
namespace tests
{
namespace char_expression
{

template<class matrix_type>
struct contraction_test_square_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = 1.7;
       mat1(1,0) = 6.3;
       mat1(1,1) = 2.8;

       mat2(0,0) = 4.4;
       mat2(0,1) = 6.1;
       mat2(1,0) = 7.4;
       mat2(1,1) = 5.5;
   
       cindex<'i'> i;
       cindex<'j'> j;
       cindex<'k'> k;

       mat0(i,k) = mat1(i,j) * mat2(j,k);

       UNIT_ASSERT(numeric::float_eq(mat0(0,0),23.58), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),24.60), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),48.44), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),53.83), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct contraction_test_square_mat_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 1.3;
       mat1(0,1) = 0.1;
       mat1(1,0) = 8.8;
       mat1(1,1) = 1.9;
       
       mat2(0,0) = 4.4;
       mat2(0,1) = 6.1;
       mat2(1,0) = 7.4;
       mat2(1,1) = 5.5;
   
       cindex<'i'> i;
       cindex<'j'> j;
       cindex<'k'> k;

       mat0(i,k) = mat1(i,j) * mat2(k,j);

       UNIT_ASSERT(numeric::float_eq(mat0(0,0),6.33), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),10.17), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),50.31), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),75.57), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct contraction_test_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);
       matrix_type mat2(3,3);

       mat1(0,0) = 11.3;
       mat1(0,1) = 1.75;
       mat1(0,2) = 51.7;
       mat1(1,0) = 44.3;
       mat1(1,1) = -94.6;
       mat1(1,2) = -9.65;

       mat2(0,0) = 66.7;
       mat2(0,1) = 75.4;
       mat2(0,2) = 45.4;
       mat2(1,0) = 3.45;
       mat2(1,1) = 1.01;
       mat2(1,2) = -21.1;
       mat2(2,0) = 53.4;
       mat2(2,1) = 0.11;
       mat2(2,2) = 7.11;
   
       cindex<'i'> i;
       cindex<'j'> j;
       cindex<'k'> k;

       mat0(i,k) = mat1(i,j) * mat2(j,k);

       UNIT_ASSERT(numeric::float_eq(mat0(0,0),3520.5275), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),859.4745), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),843.682), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),2113.130), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),3243.6125), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),3938.6685), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type, class vector_type>
struct contraction_test_mat_vec: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       vector_type vec0(3);
       matrix_type mat1(3,2);
       vector_type vec2(2);

       mat1(0,0) = 2.5;
       mat1(0,1) = 1.7;
       mat1(1,0) = 8.2;
       mat1(1,1) = 3.6;
       mat1(2,0) = 0.6;
       mat1(2,1) = 5.9;

       vec2(0) = -4.4;
       vec2(1) = 1.0;
   
       cindex<'i'> i;
       cindex<'j'> j;

       vec0(i) = mat1(i,j) * vec2(j);
      
       UNIT_ASSERT(numeric::float_eq(vec0(0),-9.30), " vec0(0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(vec0(1),-32.48), " vec0(1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(vec0(2),3.26), " vec0(2) is wrong ");
   }
};

template<class matrix_type>
struct contraction_addition_test_square_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);
       matrix_type mat3(2,2);
       matrix_type mat4(2,2);

       mat1(0,0) = 1.3;
       mat1(0,1) = 9.4;
       mat1(1,0) = 8.8;
       mat1(1,1) = 1.1;

       mat2(0,0) = 4.2;
       mat2(0,1) = 6.6;
       mat2(1,0) = 3.3;
       mat2(1,1) = 6.1;
       
       mat3(0,0) = 3.4;
       mat3(0,1) = 4.5;
       mat3(1,0) = 5.6;
       mat3(1,1) = 6.7;
       
       mat4(0,0) = 1.1;
       mat4(0,1) = 1.2;
       mat4(1,0) = 2.1;
       mat4(1,1) = 2.2;
   
       cindex<'i'> i;
       cindex<'j'> j;
       cindex<'k'> k;

       mat0(i,k) = mat1(i,j) * mat2(j,k)  +  mat3(i,j) * mat4(j,k);
       
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),49.67), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),79.90), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),60.82), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),86.25), " mat0(1,1) is wrong ");
   }
};

template<class tensor_type, class matrix_type, class vector_type>
struct contraction_test_tens3d_mat_vec: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       tensor_type tens1(2,2,2);
       vector_type vec2(2);

       tens1(0,0,0) = 1.3;
       tens1(0,0,1) = 9.4;
       tens1(0,1,0) = 8.8;
       tens1(0,1,1) = 4.7;
       tens1(1,0,0) = 2.3;
       tens1(1,0,1) = 5.4;
       tens1(1,1,0) = 7.8;
       tens1(1,1,1) = 1.0;

       vec2(0) = 4.2;
       vec2(1) = 6.6;
       
       cindex<'i'> i;
       cindex<'j'> j;
       cindex<'k'> k;

       mat0(i,j) = tens1(i,j,k) * vec2(k);
       
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),67.50), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),67.98), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),45.30), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),39.36), " mat0(1,1) is wrong ");
   }
};

} // namespace char_expression
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_CHAR_EXPRESSION_CONTRACTION_TEST_H */
