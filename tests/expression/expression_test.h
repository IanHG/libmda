#ifndef LIBMDA_TESTS_EXPRESSION_TEST_H
#define LIBMDA_TESTS_EXPRESSION_TEST_H

#include<typeinfo> // for typeid
#include<iostream>
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../expr/cindex.h"
#include "../../util/require.h"

namespace libmda
{
namespace tests
{
namespace expression
{

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct addition_square_mat_test: public virtual unit_test
{
   void do_test() 
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
   
       mat0 = mat1 + mat2;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),6.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),7.8), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),13.7), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),8.3), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct subtraction_square_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = 1.7;
       mat1(1,0) = 6.3;
       mat1(1,1) = 2.8;

       mat2(0,0) = 4.4;
       mat2(0,1) = 1.1;
       mat2(1,0) = 4.4;
       mat2(1,1) = 5.5;
   
       mat0 = mat1 - mat2;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),-1.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),0.6), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),1.9), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),-2.7), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct multiplication_square_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = 1.7;
       mat1(1,0) = 6.3;
       mat1(1,1) = 2.8;

       mat2(0,0) = 4.4;
       mat2(0,1) = 1.1;
       mat2(1,0) = -4.4;
       mat2(1,1) = -5.5;
   
       mat0 = mat1 * mat2;
        
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),11.0), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),1.87), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),-27.72), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),-15.40), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct division_square_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = -1.7;
       mat1(1,0) = -6.3;
       mat1(1,1) = 2.8;

       mat2(0,0) = 4.4;
       mat2(0,1) = 1.1;
       mat2(1,0) = -4.4;
       mat2(1,1) = -5.5;
   
       mat0 = mat1 / mat2;
        
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),0.56818181818181818181), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),-1.54545454545454545454), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),1.43181818181818181818), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),-.50909090909090909090), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct plusequal_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);

       mat0(0,0) = 2.5;
       mat0(0,1) = 1.7;
       mat0(0,2) = 1.1;
       mat0(1,0) = 6.3;
       mat0(1,1) = 2.8;
       mat0(1,2) = 2.9;

       mat1(0,0) = -4.4;
       mat1(0,1) = 6.1;
       mat1(0,2) = -1.1;
       mat1(1,0) = 7.4;
       mat1(1,1) = 5.5;
       mat1(1,2) = -4.5;
   
       mat0 += mat1;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),-1.9), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),7.8), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),0.0), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),13.7), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),8.3), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),-1.6), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct cos_sin_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);

       mat1(0,0) = -4.4;
       mat1(0,1) = 6.1;
       mat1(0,2) = -1.1;
       mat1(1,0) = 7.4;
       mat1(1,1) = 5.5;
       mat1(1,2) = -4.5;
   
       mat0 = cos(mat1)*cos(mat1)+sin(mat1)*sin(mat1);
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),1.0), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),1.0), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),1.0), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),1.0), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),1.0), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),1.0), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct mat_equal_scalar_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);

       //mat0 = scal(2.3);
       mat0 = 2.3;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),2.3), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),2.3), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),2.3), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),2.3), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),2.3), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),2.3), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct mat_minusequal_scalar_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);

       mat0(0,0) = -4.4;
       mat0(0,1) = 6.1;
       mat0(0,2) = -1.1;
       mat0(1,0) = 7.4;
       mat0(1,1) = 5.5;
       mat0(1,2) = -4.5;
   
       //mat0 -= scal(1.0);
       mat0 -= 1.0;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),-5.4), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),5.1), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),-2.1), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),6.4), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),4.5), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),-5.5), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct scalar_mat_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);

       mat1(0,0) = -4.4;
       mat1(0,1) = 6.1;
       mat1(0,2) = -1.1;
       mat1(1,0) = 7.4;
       mat1(1,1) = 5.5;
       mat1(1,2) = -4.5;
   
       //mat0 = scal(2.0) * mat1;
       mat0 = 2.0 * mat1;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),-8.8), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),12.2), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),-2.2), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),14.8), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),11.0), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),-9.0), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct mat_scalar_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,3);
       matrix_type mat1(2,3);

       mat1(0,0) = -4.4;
       mat1(0,1) = 6.1;
       mat1(0,2) = -1.1;
       mat1(1,0) = 7.4;
       mat1(1,1) = 5.5;
       mat1(1,2) = -4.5;
   
       //mat0 = mat1 + scal(1.1);
       mat0 = mat1 + 1.1;
         
       UNIT_ASSERT(numeric::float_eq(mat0(0,0),-3.3), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1),7.2), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,2),0.0), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),8.5), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1),6.6), " mat0(1,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,2),-3.4), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct scalar_mat_expr_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);
       matrix_type mat2(2,2);

       mat1(0,0) = 2.5;
       mat1(0,1) = -1.7;
       mat1(1,0) = -6.3;
       mat1(1,1) = 2.8;

       mat2(0,0) = 4.4;
       mat2(0,1) = 1.1;
       mat2(1,0) = -4.4;
       mat2(1,1) = -5.5;
   
       mat0 = 2.0 * (mat1 + mat2);
        
       UNIT_ASSERT(numeric::float_eq(mat0(0,0), 13.8), " mat0(0,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(0,1), -1.2), " mat0(0,1) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,0),-21.4), " mat0(1,0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(mat0(1,1), -5.4), " mat0(1,1) is wrong ");
   }
};

template<class matrix_type
       , util::Require_order<matrix_type,2> = 0
       >
struct mat_unary_minus_test: public virtual unit_test
{
   void do_test() 
   {
       matrix_type mat0(2,2);
       matrix_type mat1(2,2);

       mat1(0,0) = -4.4; mat1(0,1) = 6.1;
       mat1(1,0) =  7.4; mat1(1,1) = 5.5;
   
       mat0 = -mat1;
         
       UNIT_ASSERT_FEQUAL(mat0(0,0), 4.4, " mat0(0,0) is wrong ");
       UNIT_ASSERT_FEQUAL(mat0(0,1),-6.1, " mat0(0,1) is wrong ");
       UNIT_ASSERT_FEQUAL(mat0(1,0),-7.4, " mat0(1,0) is wrong ");
       UNIT_ASSERT_FEQUAL(mat0(1,1),-5.5, " mat0(1,1) is wrong ");
   }
};

template<class vector_type
       , util::Require_order<vector_type,1> = 0
       >
struct vec_unary_minus_test: public virtual unit_test
{
   void do_test() 
   {
      vector_type vec0(2);
      vector_type vec1(2);

      vec1(0) = 2.0; vec1(1) = -5.0;
   
      vec0 = -vec1;
   
      UNIT_ASSERT_FEQUAL(vec0(0),-2.0, "vec0(0) incorrect");
      UNIT_ASSERT_FEQUAL(vec0(1), 5.0, "vec0(1) incorrect");
   };
};

template<class vector_type
       , util::Require_order<vector_type,1> = 0
       >
struct vec_scalar_test: public virtual unit_test
{
   void do_test() 
   {
       vector_type vec0(2); vector_type vec1(2);

       vec1(0) = -4.4; vec1(1) = 6.1;
   
       vec0 = 1.1*vec1;
         
       UNIT_ASSERT(numeric::float_eq(vec0(0),-4.84), " vec0(0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(vec0(1), 6.71), " vec0(1) is wrong ");
   }
};

template<class vector_type
       , util::Require_order<vector_type,1> = 0
       >
struct vec_scalar_test2: public virtual unit_test
{
   void do_test() 
   {
       vector_type vec0(2); vector_type vec1(2); vector_type vec2(2);

       vec1(0) = -4.4; vec1(1) = 6.1;
       vec2(0) =  2.1; vec2(1) = 3.3;
   
       vec0 = 1.1*vec1 + vec2;
       
       UNIT_ASSERT(numeric::float_eq(vec0(0),-2.74), " vec0(0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(vec0(1),10.01), " vec0(1) is wrong ");
   }
};

template<class vector_type
       , util::Require_order<vector_type,1> = 0
       >
struct vec_char_expr_expr_test: public virtual unit_test
{  
   void do_test() 
   {
      vector_type vec1(2), vec2(2), vec3(2);

      vec1(0) = 1.1; vec1(1) = 2.0;
      vec2(0) = 2.2; vec2(1) = 1.0;
      vec3(0) = 1.0; vec3(1) = 1.2;

      cindex<'i'> i;

      typename vector_type::value_type res = ((vec1 + vec2)(i)*vec3(i)).at();
      UNIT_ASSERT(numeric::float_eq(res,6.90), " res is wrong ");
   }
};

template<class vector_type
       , class complex_vector_type
       , util::Require_order<vector_type,1> = 0
       , util::Require_order<complex_vector_type,1> = 0
       >
struct vec_complex_float_test: public virtual unit_test
{
   void do_test() 
   {
       complex_vector_type vec0(2); vector_type vec1(2); complex_vector_type vec2(2);

       vec1(0) =  2.1; vec1(1) = 3.3;
       vec2(0) = {-4.4, 3.1}; vec2(1) = {6.1,-2.0};
   
       vec0 = 1.1*vec1 + vec2;
       
       UNIT_ASSERT(numeric::float_eq(vec0(0),{-2.09, 3.10}), " vec0(0) is wrong ");
       UNIT_ASSERT(numeric::float_eq(vec0(1),{ 9.73,-2.00}), " vec0(1) is wrong ");
   }
};

} // namespace char_expression
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_EXPRESSION_TEST_H */
