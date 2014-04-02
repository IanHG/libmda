#ifndef LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED
#define LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits

// std midas
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../testing/float_is_equal.h"

namespace libmda
{
namespace numeric_test
{

struct float_eq_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       double a = 1.0; double b = 2.0;
       double c = 3.0; double d = 4.0;

       UNIT_ASSERT( numeric::float_eq(a,a),"");
       UNIT_ASSERT(!numeric::float_eq(a,b),"");
       UNIT_ASSERT( numeric::float_eq(a+d,b+c),"");
       UNIT_ASSERT(!numeric::float_eq(a+c,b+d),"");
       UNIT_ASSERT( numeric::float_eq(b-d,a-c),"");
       UNIT_ASSERT(!numeric::float_eq(a-d,a-c),"");
       
       double a2 = 1.0; 
       double b2 = a2 + std::numeric_limits<double>::epsilon();
       double c2 = a2 + 2.0*std::numeric_limits<double>::epsilon();
       UNIT_ASSERT(!numeric::float_eq(a2,b2,0),"");
       UNIT_ASSERT( numeric::float_eq(a2,b2,1),"");
       UNIT_ASSERT(!numeric::float_eq(a2,c2,0),"");
       UNIT_ASSERT(!numeric::float_eq(a2,c2,1),"");
       UNIT_ASSERT( numeric::float_eq(a2,c2,2),"");
       
       float a3 = 1.0; 
       float b3 = a3 + std::numeric_limits<float>::epsilon();
       float c3 = a3 + 2.0*std::numeric_limits<float>::epsilon();
       UNIT_ASSERT(!numeric::float_eq(a3,b3,0),"");
       UNIT_ASSERT( numeric::float_eq(a3,b3,1),"");
       UNIT_ASSERT(!numeric::float_eq(a3,c3,0),"");
       UNIT_ASSERT(!numeric::float_eq(a3,c3,1),"");
       UNIT_ASSERT( numeric::float_eq(a3,c3,2),"");
       
       numeric::int_float<double> ifa(1);
       numeric::int_float<double> ifb(2);

       UNIT_ASSERT(!numeric::float_eq(ifa.m_float,ifb.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifa.m_float,ifb.m_float,1),"");
       UNIT_ASSERT( numeric::float_eq(ifb.m_float-ifa.m_float,ifa.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifb.m_float-ifa.m_float,ifa.m_float),"");
       
       numeric::int_float<float> ifa2(1);
       numeric::int_float<float> ifb2(2);

       UNIT_ASSERT(!numeric::float_eq(ifa2.m_float,ifb2.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifa2.m_float,ifb2.m_float,1),"");
       UNIT_ASSERT( numeric::float_eq(ifb2.m_float-ifa2.m_float,ifa2.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifb2.m_float-ifa2.m_float,ifa2.m_float),"");
       
       numeric::int_float<double> ifa3(1337);
       numeric::int_float<double> ifb3(337);

       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float,0),"");
       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float),"");
       UNIT_ASSERT( numeric::float_eq(ifa3.m_float,ifb3.m_float,1000),"");
       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float,999),"");
       UNIT_ASSERT( numeric::float_eq(ifa3.m_float-ifb3.m_float,ifa3.m_float,337),"");
   }
};

struct float_neq_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       double a = 1.0; double b = 2.0;
       double c = 3.0; double d = 4.0;

       UNIT_ASSERT(!numeric::float_neq(a,a),"");
       UNIT_ASSERT( numeric::float_neq(a,b),"");
       UNIT_ASSERT(!numeric::float_neq(a+d,b+c),"");
       UNIT_ASSERT( numeric::float_neq(a+c,b+d),"");
       UNIT_ASSERT(!numeric::float_neq(b-d,a-c),"");
       UNIT_ASSERT( numeric::float_neq(a-d,a-c),"");
       
       double a2 = 1.0; 
       double b2 = a2 + std::numeric_limits<double>::epsilon();
       double c2 = a2 + 2.0*std::numeric_limits<double>::epsilon();
       UNIT_ASSERT( numeric::float_neq(a2,b2,0),"");
       UNIT_ASSERT(!numeric::float_neq(a2,b2,1),"");
       UNIT_ASSERT( numeric::float_neq(a2,c2,0),"");
       UNIT_ASSERT( numeric::float_neq(a2,c2,1),"");
       UNIT_ASSERT(!numeric::float_neq(a2,c2,2),"");
       
       float a3 = 1.0; 
       float b3 = a3 + std::numeric_limits<float>::epsilon();
       float c3 = a3 + 2.0*std::numeric_limits<float>::epsilon();
       UNIT_ASSERT( numeric::float_neq(a3,b3,0),"");
       UNIT_ASSERT(!numeric::float_neq(a3,b3,1),"");
       UNIT_ASSERT( numeric::float_neq(a3,c3,0),"");
       UNIT_ASSERT( numeric::float_neq(a3,c3,1),"");
       UNIT_ASSERT(!numeric::float_neq(a3,c3,2),"");
       
       numeric::int_float<double> ifa(1);
       numeric::int_float<double> ifb(2);

       UNIT_ASSERT( numeric::float_neq(ifa.m_float,ifb.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifa.m_float,ifb.m_float,1),"");
       UNIT_ASSERT(!numeric::float_neq(ifb.m_float-ifa.m_float,ifa.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifb.m_float-ifa.m_float,ifa.m_float),"");
       
       numeric::int_float<float> ifa2(1);
       numeric::int_float<float> ifb2(2);

       UNIT_ASSERT( numeric::float_neq(ifa2.m_float,ifb2.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifa2.m_float,ifb2.m_float,1),"");
       UNIT_ASSERT(!numeric::float_neq(ifb2.m_float-ifa2.m_float,ifa2.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifb2.m_float-ifa2.m_float,ifa2.m_float),"");
       
       numeric::int_float<double> ifa3(1337);
       numeric::int_float<double> ifb3(337);

       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float,0),"");
       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float),"");
       UNIT_ASSERT(!numeric::float_neq(ifa3.m_float,ifb3.m_float,1000),"");
       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float,999),"");
       UNIT_ASSERT(!numeric::float_neq(ifa3.m_float-ifb3.m_float,ifa3.m_float,337),"");
   }
};

struct float_sign_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      double a = 2.0;
      UNIT_ASSERT( numeric::float_pos(a),"");
      UNIT_ASSERT(!numeric::float_neg(a),"");
      
      double neg_a = -2.0;
      UNIT_ASSERT(!numeric::float_pos(neg_a),"");
      UNIT_ASSERT( numeric::float_neg(neg_a),"");
   
      double zero = 0.0;
      UNIT_ASSERT( numeric::float_pos(zero),"");
      UNIT_ASSERT(!numeric::float_neg(zero),"");
      
      double neg_zero = -0.0;
      UNIT_ASSERT(!numeric::float_pos(neg_zero),"");
      UNIT_ASSERT( numeric::float_neg(neg_zero),"");
   }
};

} /* namespace numeric_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED */
