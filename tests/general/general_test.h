#ifndef LIBMDA_TESTS_GENERAL_TEST_H
#define LIBMDA_TESTS_GENERAL_TEST_H

#include<iostream>

#include "../../interface.h"
#include "../../testing/testing_interface.h"

namespace libmda
{
namespace tests
{
namespace general
{

template<class vector_type>
struct vector_construction_test: public virtual unit_test
{
   typedef typename vector_type::size_type size_type;
   size_type m_size;

   vector_construction_test(size_type a_size = size_type(0)): m_size(a_size) { };
   
   void do_test() throw(test_failed)
   { 
      vector_type vec(m_size);
      UNIT_ASSERT_EQUAL(vec.size(),m_size,"vec size not correct after construction");
   }
};

template<class vector_type>
struct vector_copy_construction_test: public virtual unit_test
{
   typedef typename vector_type::size_type  size_type;
   typedef typename vector_type::value_type value_type;
   
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      vector_type vec0(size);
      for(size_type i=0; i<size; ++i) vec0(i) = value_type(i);
      vector_type vec1(vec0);
      for(size_type i=0; i<size; ++i) 
      { UNIT_ASSERT_FEQUAL(vec1(i),vec0(i),"element not copied correctly"); }
   }
};

template<class vector_type>
struct vector_implicit_copy_construction_test: public virtual unit_test
{
   typedef typename vector_type::size_type  size_type;
   typedef typename vector_type::value_type value_type;
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      vector_type vec0(size);
      for(size_type i=0; i<size; ++i) vec0(i) = value_type(i);
      vector_type vec1 = vec0;
      for(size_type i=0; i<size; ++i)
      { UNIT_ASSERT_FEQUAL(vec1(i),vec0(i),"element not implicitly copied correctly"); }
   }
};

template<class vector_type>
struct vector_copy_assignment_test: public virtual unit_test
{
   typedef typename vector_type::size_type  size_type;
   typedef typename vector_type::value_type value_type;
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      vector_type vec0(size);
      for(size_type i=0; i<size; ++i) vec0(i) = value_type(i);
      vector_type vec1(size);
      vec1 = vec0;
      for(size_type i=0; i<size; ++i)
      { UNIT_ASSERT_FEQUAL(vec1(i),vec0(i),"element not assigned correctly"); }
   }
};

template<class matrix_type>
struct matrix_construction_test: public virtual unit_test
{
   typedef typename matrix_type::size_type size_type;
   size_type m_rows;
   size_type m_cols;

   matrix_construction_test(size_type a_rows = size_type(0),
                            size_type a_cols = size_type(0)): 
      m_rows(a_rows), m_cols(a_cols) { };
   
   void do_test() throw(test_failed)
   { 
      matrix_type mat(m_rows,m_cols);
      UNIT_ASSERT_EQUAL(mat.template extent<0>(),m_rows,"mat rows not correct after construction");
      UNIT_ASSERT_EQUAL(mat.template extent<1>(),m_cols,"mat cols not correct after construction");
   }
};

template<class matrix_type>
struct matrix_copy_construction_test: public virtual unit_test
{
   typedef typename matrix_type::size_type  size_type;
   typedef typename matrix_type::value_type value_type;
   
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      matrix_type mat0(size,size);
      for(size_type i=0; i<size; ++i) 
         for(size_type j=0; j<size; ++j) mat0(i,j) = value_type(i+j);
      matrix_type mat1(mat0);
      for(size_type i=0; i<size; ++i) 
         for(size_type j=0; j<size; ++j) 
         { UNIT_ASSERT_FEQUAL(mat1(i,j),mat0(i,j),"element not copied correctly"); }
   }
};

template<class matrix_type>
struct matrix_implicit_copy_construction_test: public virtual unit_test
{
   typedef typename matrix_type::size_type  size_type;
   typedef typename matrix_type::value_type value_type;
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      matrix_type mat0(size,size);
      for(size_type i=0; i<size; ++i) 
         for(size_type j=0; j<size; ++j) mat0(i,j) = value_type(i+j);
      matrix_type mat1 = mat0;
      for(size_type i=0; i<size; ++i)
         for(size_type j=0; j<size; ++j) 
         { UNIT_ASSERT_FEQUAL(mat1(i,j),mat0(i,j),"element not implicitly copied correctly"); }
   }
};

template<class matrix_type>
struct matrix_copy_assignment_test: public virtual unit_test
{
   typedef typename matrix_type::size_type  size_type;
   typedef typename matrix_type::value_type value_type;
   void do_test() throw(test_failed)
   {
      size_type size = 3;
      matrix_type mat0(size,size);
      for(size_type i=0; i<size; ++i) 
         for(size_type j=0; j<size; ++j) mat0(i,j) = value_type(i+j);
      matrix_type mat1(size,size);
      mat1 = mat0;
      for(size_type i=0; i<size; ++i)
         for(size_type j=0; j<size; ++j) 
         { UNIT_ASSERT_FEQUAL(mat1(i,j),mat0(i,j),"element not assigned correctly"); }
   }
};

} // namespace general
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_GENERAL_TEST_H */
