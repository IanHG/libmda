#ifndef LIBMDA_TESTS_CHAR_EXPRESSION_ADDITION_TEST_H
#define LIBMDA_TESTS_CHAR_EXPRESSION_ADDITION_TEST_H

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
struct addition_test_square_mat: public virtual unit_test
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

       mat0(i,j) = mat1(i,j) + mat2(i,j);

       UNIT_ASSERT(float_is_equal(mat0(0,0),6.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),7.8), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),13.7), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),8.3), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct plusequal_test_square_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);

       mat0(0,0) = 1.3;
       mat0(0,1) = 5.7;
       mat0(1,0) = 9.4;
       mat0(1,1) = 3.6;

       mat1(0,0) = 1.3;
       mat1(0,1) = 0.1;
       mat1(1,0) = 8.8;
       mat1(1,1) = 1.9;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(i,j) += mat1(i,j);

       UNIT_ASSERT(float_is_equal(mat0(0,0),2.6), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),5.8), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),18.2), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),5.5), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct minusequal_test_square_mat_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);

       mat0(0,0) = 11.3;
       mat0(0,1) = 1.75;
       mat0(1,0) = 44.3;
       mat0(1,1) = 94.6;

       mat1(0,0) = 66.7;
       mat1(0,1) = 75.4;
       mat1(1,0) = 3.45;
       mat1(1,1) = 0.01;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(i,j) -= mat1(j,i);

       UNIT_ASSERT(float_is_equal(mat0(0,0),-55.4), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),-1.70), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),-31.1), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),94.59), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct subtraction_test_square_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = 1.7;
       mat1(1,0) = 8.2;
       mat1(1,1) = 3.6;

       mat2(0,0) = 4.4;
       mat2(0,1) = 6.1;
       mat2(1,0) = 2.2;
       mat2(1,1) = 1.0;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(i,j) = mat1(i,j) - mat2(i,j);
      
       UNIT_ASSERT(float_is_equal(mat0(0,0),-1.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),-4.4), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),6.0), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),2.6), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct addition_test_square_mat_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 1.3;
       mat1(0,1) = 9.4;
       mat1(1,0) = 8.8;
       mat1(1,1) = 1.1;

       mat2(0,0) = 4.2;
       mat2(0,1) = 6.6;
       mat2(1,0) = 3.3;
       mat2(1,1) = 6.1;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(j,i) = mat1(i,j) + mat2(j,i);
         
       UNIT_ASSERT(float_is_equal(mat0(0,0),5.5), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),15.4), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),12.7), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),7.2), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct subtraction_test_square_mat_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 1.3;
       mat1(0,1) = 9.4;
       mat1(1,0) = 8.8;
       mat1(1,1) = 1.1;

       mat2(0,0) = 4.2;
       mat2(0,1) = 6.6;
       mat2(1,0) = 3.3;
       mat2(1,1) = 6.1;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(j,i) = mat1(j,i) - mat2(i,j);
         
       UNIT_ASSERT(float_is_equal(mat0(0,0),-2.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),6.1), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),2.2), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),-5.0), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct addition_test_mat: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);
       matrix_type mat2(2,3);

       mat1(0,0) = 2.2;
       mat1(0,1) = 3.3;
       mat1(0,2) = 4.4;
       mat1(1,0) = 5.5;
       mat1(1,1) = 6.6;
       mat1(1,2) = 7.7;

       mat2(0,0) = 9.1;
       mat2(0,1) = 8.2;
       mat2(0,2) = 7.3;
       mat2(1,0) = 6.4;
       mat2(1,1) = 5.5;
       mat2(1,2) = 4.6;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(i,j) = mat1(i,j) + mat2(i,j);

       UNIT_ASSERT(float_is_equal(mat0(0,0),11.3), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),11.5), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,2),11.7), " mat0(0,2) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),11.9), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),12.1), " mat0(1,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,2),12.3), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct addition_test_mat_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(3,2);
       matrix_type mat1(2,3);
       matrix_type mat2(2,3);

       mat1(0,0) = 2.2;
       mat1(0,1) = 3.3;
       mat1(0,2) = 4.4;
       mat1(1,0) = 5.5;
       mat1(1,1) = 6.6;
       mat1(1,2) = 7.7;

       mat2(0,0) = 9.1;
       mat2(0,1) = 8.2;
       mat2(0,2) = 7.3;
       mat2(1,0) = 6.4;
       mat2(1,1) = 5.5;
       mat2(1,2) = 4.6;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(j,i) = mat1(i,j) + mat2(i,j);

       UNIT_ASSERT(float_is_equal(mat0(0,0),11.3), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),11.9), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),11.5), " mat0(0,2) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),12.1), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(2,0),11.7), " mat0(1,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(2,1),12.3), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type>
struct addition_test_mat_trans_2: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       matrix_type mat0(3,2);
       matrix_type mat1(2,3);
       matrix_type mat2(2,3);
       matrix_type mat3(3,2);

       mat1(0,0) = 2.2;
       mat1(0,1) = 3.3;
       mat1(0,2) = 4.4;
       mat1(1,0) = 5.5;
       mat1(1,1) = 6.6;
       mat1(1,2) = 7.7;

       mat2(0,0) = 9.1;
       mat2(0,1) = 8.2;
       mat2(0,2) = 7.3;
       mat2(1,0) = 6.4;
       mat2(1,1) = 5.5;
       mat2(1,2) = 4.6;
       
       mat3(0,0) = 1.1;
       mat3(0,1) = 1.0;
       mat3(1,0) = 0.9;
       mat3(1,1) = 0.8;
       mat3(2,0) = 0.7;
       mat3(2,1) = 0.6;
   
       cindex<'i'> i;
       cindex<'j'> j;

       mat0(j,i) = mat1(i,j) + mat2(i,j) - mat3(j,i);

       UNIT_ASSERT(float_is_equal(mat0(0,0),10.2), " mat0(0,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(0,1),10.9), " mat0(0,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,0),10.6), " mat0(0,2) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(1,1),11.3), " mat0(1,0) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(2,0),11.0), " mat0(1,1) is wrong ");
       UNIT_ASSERT(float_is_equal(mat0(2,1),11.7), " mat0(1,1) is wrong ");
   }
};

} // namespace char_expression
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_CHAR_EXPRESSION_ADDITION_TEST_H */
