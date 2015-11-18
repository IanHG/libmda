#ifndef LIBMDA_TESTS_UTIL_ANY_TYPE_H_INCLUDED
#define LIBMDA_TESTS_UTIL_ANY_TYPE_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits
#include <type_traits>
#include <string>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/any_type.h"
#include "../../util/type_info.h"

namespace libmda
{
namespace tests
{
namespace util
{

/**
 *
 **/
struct any_type_nulltype_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      libmda::util::any_type any;
      UNIT_ASSERT_EQUAL( std::string(any.type_name())
                       , std::string(std::type_index(typeid(nullptr)).name())
                       , "default constructed not nullptr type."
                       );
   }
};

/**
 *
 **/
template<class T>
struct any_type_type_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      libmda::util::any_type any(static_cast<T>(0));
      UNIT_ASSERT_EQUAL( std::string(any.type_name())
                       , std::string(std::type_index(typeid(T)).name())
                       , "construction failed from type: " + libmda::util::typeof<T>()
                       );
   }
};

/**
 *
 **/
struct any_type_get_noexception_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      libmda::util::any_type any_double(static_cast<double>(3.14159));
      try
      {
         UNIT_ASSERT_FEQUAL(any_double.get<double>(), static_cast<double>(3.14159), "libmda::util::any_type::get() failed: returned wrong value");
      }
      catch(std::exception& e)
      {
         UNIT_ASSERT(false,"libmda::util::any_type::get() failed: excetion was raised.");
      }
   }
};

/**
 *
 **/
struct any_type_get_exception_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      libmda::util::any_type any_double(static_cast<double>(3.14159));
      try
      {
         any_double.get<float>();
         UNIT_ASSERT(false,"libmda::util::any_type::get() failed: exception was NOT raised.");
      }
      catch(std::exception& e)
      {
         UNIT_ASSERT_FEQUAL(any_double.get<double>(), static_cast<double>(3.14159), "libmda::util::any_type::get() failed: returned wrong value");
      }
   }
};


} /* namespace util */
} /* namespace tests */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_UTIL_ANY_TYPE_H_INCLUDED */
