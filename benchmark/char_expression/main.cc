#include<iostream>
using std::cout;
using std::endl;
#include "../../testing/testing_interface.h"
#include "../../arrays/SDArray2D.h"
using midas::mmv::SDArray2D;
#include "../../arrays/MultiDimArray.h"
using libmda::MDA;
#include "../../expr/cindex.h"
using libmda::cindex;

#ifndef MATRIX_SIZE
#define MATRIX_SIZE 600
#endif /* MATRIX_SIZE */

template<class matrix_type>
struct basic_mat_mult: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      
      for(size_type i=0; i<size; ++i)
         for(size_type j=0; j<size; ++j)
         {
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
         }
      
      double elem;

      for(size_type i=0; i<mat0.template dim<0>(); ++i)
         for(size_type j=0; j<mat0.template dim<1>(); ++j)
         {
            elem = 0;
            for(size_type k=0; k<mat1.template dim<1>(); ++k)
               elem += mat1(i,k)*mat2(k,j);
            mat0(i,j) = elem;
         }

      //cout << mat0 << endl;
   }
};

template<class matrix_type>
struct basic_mat_mult_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      
      for(int i=0; i<size; ++i)
         for(int j=0; j<size; ++j)
         {
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
         }
      
      double elem;

      for(size_type j=0; j<mat0.template dim<0>(); ++j)
         for(size_type i=0; i<mat0.template dim<1>(); ++i)
         {
            elem = 0;
            for(size_type k=0; k<mat1.template dim<1>(); ++k)
               elem += mat1(i,k)*mat2(k,j);
            mat0(j,i) = elem;
         }

      //cout << mat0 << endl;
   }
};

template<class matrix_type>
struct libmda_mat_mult: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      
      for(int i=0; i<size; ++i)
         for(int j=0; j<size; ++j)
         {
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
         }
      
      cindex<'i'> i;
      cindex<'j'> j;
      cindex<'k'> k;

      mat0(i,j)=mat1(i,k)*mat2(k,j);
      
      //cout << mat0 << endl;
   }
};

template<class matrix_type>
struct libmda_mat_mult_trans: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      
      for(int i=0; i<size; ++i)
         for(int j=0; j<size; ++j)
         {
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
         }
      
      cindex<'i'> i;
      cindex<'j'> j;
      cindex<'k'> k;

      mat0(j,i)=mat1(i,k)*mat2(k,j);
      
      //cout << mat0 << endl;
   }
};

template<class matrix_type>
struct basic_mat_expr: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      matrix_type mat3(size,size);
      
      for(size_type i=0; i<size; ++i)
         for(size_type j=0; j<size; ++j)
         {
            mat0(i,j) = 2+i;
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
            mat3(i,j) = i*j;
         }
      
      double elem;

      for(size_type i=0; i<mat0.template dim<0>(); ++i)
         for(size_type j=0; j<mat0.template dim<1>(); ++j)
         {
            elem = 0;
            for(size_type k=0; k<mat1.template dim<1>(); ++k)
               elem += mat1(i,k)*mat2(k,j);
            mat0(i,j) += elem - mat3(i,j);
         }

      //cout << mat0 << endl;
   }
};

template<class matrix_type>
struct libmda_mat_expr: public virtual unit_test
{
   void do_test() throw(test_failed)
   { 
      typedef typename matrix_type::size_type size_type;
      size_type size=MATRIX_SIZE;
      matrix_type mat0(size,size);
      matrix_type mat1(size,size);
      matrix_type mat2(size,size);
      matrix_type mat3(size,size);
      
      for(int i=0; i<size; ++i)
         for(int j=0; j<size; ++j)
         {
            mat0(i,j) = 2+i;
            mat1(i,j) = i+j;
            mat2(j,i) = 2*j;
            mat3(i,j) = i*j;
         }
      
      cindex<'i'> i;
      cindex<'j'> j;
      cindex<'k'> k;

      mat0(i,j)+=mat1(i,k)*mat2(k,j) - mat3(i,j);
   }
};

typedef SDArray2D<double> d_matrix;
typedef MDA<double,2>     mda_matrix;

#ifndef NUM_RUN
#define NUM_RUN 1
#endif /* NUM_RUN */

int main()
{
   test_suite suite;
   
   suite.add_performance_test<NUM_RUN,basic_mat_mult<d_matrix> >();
   suite.add_performance_test<NUM_RUN,basic_mat_mult_trans<d_matrix> >();
   suite.add_performance_test<NUM_RUN,basic_mat_expr<d_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_mult<d_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_mult_trans<d_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_expr<d_matrix> >();
   
   suite.add_performance_test<NUM_RUN,basic_mat_mult<mda_matrix> >();
   suite.add_performance_test<NUM_RUN,basic_mat_mult_trans<mda_matrix> >();
   suite.add_performance_test<NUM_RUN,basic_mat_expr<mda_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_mult<mda_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_mult_trans<mda_matrix> >();
   suite.add_performance_test<NUM_RUN,libmda_mat_expr<mda_matrix> >();
   
   suite.do_tests();
   
   return 0;
}
