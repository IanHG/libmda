#ifndef LIBMDA_TESTS_UTIL_FROM_STRING_H_INCLUDED
#define LIBMDA_TESTS_UTIL_FROM_STRING_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits
#include <type_traits>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/from_string.h"

namespace libmda
{
namespace tests
{
namespace util
{

/**
 *
 **/
template<class T = double>
struct from_string_float_test: public virtual unit_test
{
   static_assert(std::is_floating_point<T>::value, "only works with floating point types");
   void do_test() 
   {
      auto a = libmda::util::from_string<T>("3.14159");

      UNIT_ASSERT_FEQUAL_PREC(a, T(3.14159),     4, "midas::util::from_string float failed for type: " + libmda::util::typeof(a));
   }
};

/**
 *
 **/
template<class T = int>
struct from_string_int_test: public virtual unit_test
{
   static_assert(std::is_integral<T>::value, "only works with integral types");
   void do_test() 
   {
      auto a = libmda::util::from_string<T>("314159");

      UNIT_ASSERT_EQUAL(a, T(314159), "midas::util::from_string integral failed for type: " + libmda::util::typeof(a));
   }
};

/**
 *
 **/
template<class T = int>
struct from_string_signed_int_test: public virtual unit_test
{
   static_assert(std::is_signed<T>::value, "only works with signed integral types");
   void do_test() 
   {
      auto a = libmda::util::from_string<T>("-314159");

      UNIT_ASSERT_EQUAL(a, T(-314159), "midas::util::from_string signed integral failed for type: " + libmda::util::typeof(a));
   }
};

} /* namespace util */
} /* namespace tests */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_UTIL_FROM_STRING_H_INCLUDED */
