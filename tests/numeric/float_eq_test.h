#ifndef LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED
#define LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits

// 
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../numeric/float_eq.h"
#include "../../util/type_info.h"

namespace libmda
{
namespace numeric_test
{

template<class T>
struct float_eq_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       T a = 1.0; T b = 2.0;
       T c = 3.0; T d = 4.0;

       UNIT_ASSERT( numeric::float_eq(a,a),"");
       UNIT_ASSERT(!numeric::float_eq(a,b),"");
       UNIT_ASSERT( numeric::float_eq(a+d,b+c),"");
       UNIT_ASSERT(!numeric::float_eq(a+c,b+d),"");
       UNIT_ASSERT( numeric::float_eq(b-d,a-c),"");
       UNIT_ASSERT(!numeric::float_eq(a-d,a-c),"");
       
       T a2 = 1.0; 
       T b2 = a2 + std::numeric_limits<T>::epsilon();
       T c2 = a2 + 2.0*std::numeric_limits<T>::epsilon();
       UNIT_ASSERT(!numeric::float_eq(a2,b2,0),"");
       UNIT_ASSERT( numeric::float_eq(a2,b2,1),"");
       UNIT_ASSERT(!numeric::float_eq(a2,c2,0),"");
       UNIT_ASSERT(!numeric::float_eq(a2,c2,1),"");
       UNIT_ASSERT( numeric::float_eq(a2,c2,2),"");
       
       numeric::int_float<T> ifa(1);
       numeric::int_float<T> ifb(2);

       UNIT_ASSERT(!numeric::float_eq(ifa.m_float,ifb.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifa.m_float,ifb.m_float,1),"");
       UNIT_ASSERT( numeric::float_eq(ifb.m_float-ifa.m_float,ifa.m_float,0),"");
       UNIT_ASSERT( numeric::float_eq(ifb.m_float-ifa.m_float,ifa.m_float),"");
       
       numeric::int_float<T> ifa3(1337);
       numeric::int_float<T> ifb3(337);

       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float,0),"");
       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float),"");
       UNIT_ASSERT( numeric::float_eq(ifa3.m_float,ifb3.m_float,1000),"");
       UNIT_ASSERT(!numeric::float_eq(ifa3.m_float,ifb3.m_float,999),"");
       UNIT_ASSERT( numeric::float_eq(ifa3.m_float-ifb3.m_float,ifa3.m_float,337),"");
   }
};

template<class T>
struct float_neq_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
       T a = 1.0; T b = 2.0;
       T c = 3.0; T d = 4.0;

       UNIT_ASSERT(!numeric::float_neq(a,a),"");
       UNIT_ASSERT( numeric::float_neq(a,b),"");
       UNIT_ASSERT(!numeric::float_neq(a+d,b+c),"");
       UNIT_ASSERT( numeric::float_neq(a+c,b+d),"");
       UNIT_ASSERT(!numeric::float_neq(b-d,a-c),"");
       UNIT_ASSERT( numeric::float_neq(a-d,a-c),"");
       
       T a2 = 1.0; 
       T b2 = a2 + std::numeric_limits<T>::epsilon();
       T c2 = a2 + 2.0*std::numeric_limits<T>::epsilon();
       UNIT_ASSERT( numeric::float_neq(a2,b2,0),"");
       UNIT_ASSERT(!numeric::float_neq(a2,b2,1),"");
       UNIT_ASSERT( numeric::float_neq(a2,c2,0),"");
       UNIT_ASSERT( numeric::float_neq(a2,c2,1),"");
       UNIT_ASSERT(!numeric::float_neq(a2,c2,2),"");
       
       numeric::int_float<T> ifa(1);
       numeric::int_float<T> ifb(2);

       UNIT_ASSERT( numeric::float_neq(ifa.m_float,ifb.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifa.m_float,ifb.m_float,1),"");
       UNIT_ASSERT(!numeric::float_neq(ifb.m_float-ifa.m_float,ifa.m_float,0),"");
       UNIT_ASSERT(!numeric::float_neq(ifb.m_float-ifa.m_float,ifa.m_float),"");
       
       numeric::int_float<T> ifa3(1337);
       numeric::int_float<T> ifb3(337);

       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float,0),"");
       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float),"");
       UNIT_ASSERT(!numeric::float_neq(ifa3.m_float,ifb3.m_float,1000),"");
       UNIT_ASSERT( numeric::float_neq(ifa3.m_float,ifb3.m_float,999),"");
       UNIT_ASSERT(!numeric::float_neq(ifa3.m_float-ifb3.m_float,ifa3.m_float,337),"");
   }
};

template<class T>
struct float_sign_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = 2.0;
      UNIT_ASSERT( numeric::float_pos(a),"sign test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_neg(a),"sign test failed for type: "+util::typeof(a));
      
      T neg_a = -2.0;
      UNIT_ASSERT(!numeric::float_pos(neg_a),"sign test failed for type: "+util::typeof(neg_a));
      UNIT_ASSERT( numeric::float_neg(neg_a),"sign test failed for type: "+util::typeof(neg_a));
   
      T zero = 0.0;
      UNIT_ASSERT( numeric::float_pos(zero),"sign test failed for type: "+util::typeof(zero));
      UNIT_ASSERT(!numeric::float_neg(zero),"sign test failed for type: "+util::typeof(zero));
      
      T neg_zero = -0.0;
      UNIT_ASSERT(!numeric::float_pos(neg_zero),"sign test failed for type: "+util::typeof(neg_zero));
      UNIT_ASSERT( numeric::float_neg(neg_zero),"sign test failed for type: "+util::typeof(neg_zero));
   }
};

template<class T>
struct float_numeq_zero_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numeq_zero(a,1.0,2),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numeq_zero(a,1.0,1),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(a,1.0,0),"numeric zero test failed for type: "+util::typeof(a));
   
      T b = 2*std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numeq_zero(b,T(1.0),2),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(b,T(1.0),1),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(b,T(1.0),0),"numeric zero test failed for type: "+util::typeof(a));
      
      //std::cout << " here " << std::endl;
      T c = -2*std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numeq_zero(c,T(1.0),4),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(c,T(1.0),3),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(c,T(1.0),2),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(c,T(1.0),1),"numeric zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numeq_zero(c,T(1.0),0),"numeric zero test failed for type: "+util::typeof(a));
      
      UNIT_ASSERT( numeric::float_numeq_zero(a*T(1e+2),T(1e+2),2),"numeric zero test failed for type: "+util::typeof(a));
   }
};

template<class T>
struct float_numgeq_zero_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numgeq_zero(a,T(1.0),1),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numgeq_zero(a,T(1.0),0),"numeric geq zero test failed for type: "+util::typeof(a));
   
      T b = -2*std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numgeq_zero(b,T(1.0),4),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numgeq_zero(b,T(1.0),3),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numgeq_zero(b,T(1.0),2),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numgeq_zero(b,T(1.0),1),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numgeq_zero(b,T(1.0),0),"numeric geq zero test failed for type: "+util::typeof(a));

      T c = 2*std::numeric_limits<T>::epsilon();
      // will always be true for positive numbers
      UNIT_ASSERT( numeric::float_numgeq_zero(c,T(1.0),2),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numgeq_zero(c,T(1.0),1),"numeric geq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numgeq_zero(c,T(1.0),0),"numeric geq zero test failed for type: "+util::typeof(a));
   }
};

template<class T>
struct float_numleq_zero_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numleq_zero(a,T(1.0),1),"numeric leq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numleq_zero(a,T(1.0),0),"numeric leq zero test failed for type: "+util::typeof(a));
   
      T b = -2*std::numeric_limits<T>::epsilon();
      // numleq_zero will always be true for negative numbers
      UNIT_ASSERT( numeric::float_numleq_zero(b,T(1.0),2),"numeric leq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numleq_zero(b,T(1.0),1),"numeric leq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_numleq_zero(b,T(1.0),0),"numeric leq zero test failed for type: "+util::typeof(a));

      T c = 2*std::numeric_limits<T>::epsilon();
      UNIT_ASSERT( numeric::float_numleq_zero(c,T(1.0),2),"numeric leq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numleq_zero(c,T(1.0),1),"numeric leq zero test failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_numleq_zero(c,T(1.0),0),"numeric leq zero test failed for type: "+util::typeof(a));
   }
};

} /* namespace numeric_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_FLOAT_EQ_TEST_H_INCLUDED */
