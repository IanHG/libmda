#ifndef LIBMDA_TESTS_NUMERIC_H_INCLUDED
#define LIBMDA_TESTS_NUMERIC_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../numeric/float_eq.h"
#include "../../numeric/signum.h"
#include "../../util/type_info.h"

namespace libmda
{
namespace numeric_test
{

template<class T = double>
struct signum_pos_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = 2.0;
      UNIT_ASSERT( numeric::float_pos(numeric::signum(a)),"Signum pos failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_neg(numeric::signum(a)),"Signum pos failed for type: "+util::typeof(a));
   }
};

template<class T = double>
struct signum_neg_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = -3.3333;
      UNIT_ASSERT(!numeric::float_pos(numeric::signum(a)),"Signum neg failed for type: "+util::typeof(a));
      UNIT_ASSERT( numeric::float_neg(numeric::signum(a)),"Signum neg failed for type: "+util::typeof(a));
   }
};

template<class T = double>
struct signum_zero_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      T a = 0.0;
      UNIT_ASSERT( numeric::float_pos(numeric::signum(a)),"Signum pos zero failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_neg(numeric::signum(a)),"Signum pos zero failed for type: "+util::typeof(a));
      
      T b = -0.0;
      UNIT_ASSERT( numeric::float_pos(numeric::signum(b)),"Signum neg zero failed for type: "+util::typeof(a));
      UNIT_ASSERT(!numeric::float_neg(numeric::signum(b)),"Signum neg zero failed for type: "+util::typeof(a));
   }
};

} /* namespace numeric_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_NUMERIC_H_INCLUDED */
