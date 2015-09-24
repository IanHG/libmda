#ifndef LIBMDA_TESTS_UTIL_H_INCLUDED
#define LIBMDA_TESTS_UTIL_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits
#include <type_traits>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/type_info.h"
#include "../../util/pow.h"

namespace libmda
{
namespace tests
{
namespace util
{

template<class T = double>
struct pow_test: public virtual unit_test
{
   static_assert(std::is_floating_point<T>::value, "only works with floating point types");
   void do_test() throw(test_failed)
   {
      T a = 2.0;

      UNIT_ASSERT_FEQUAL_PREC(libmda::util::pow<3>(a),T(8.0),     4,"Pow failed for type: "+libmda::util::typeof(a));
      UNIT_ASSERT_FEQUAL_PREC(libmda::util::pow<3>(T(2.0)),T(8.0),4,"Pow failed for type: "+libmda::util::typeof(a));
   }
};

} /* namespace util */
} /* namespace tests */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_UTIL_H_INCLUDED */
