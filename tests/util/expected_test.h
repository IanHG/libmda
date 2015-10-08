#ifndef LIBMDA_TESTS_UTIL_EXPECTED_H_INCLUDED
#define LIBMDA_TESTS_UTIL_EXPECTED_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits
#include <type_traits>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/expected.h"

namespace libmda
{
namespace tests
{
namespace util
{

/**
 *
 **/
struct expected_no_except_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      bool except_raised = false;
      libmda::util::expected<int> i = 0;
      try
      {
         i.get();
      }
      catch(...)
      {
         except_raised = true;
      }
      UNIT_ASSERT(!except_raised, " libmda::util::expected exception was raised ");
   }
};

/**
 *
 **/
struct expected_except_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      bool except_raised = false;
      libmda::util::expected<int> i = libmda::util::expected<int>::from_exception(0);
      try
      {
         i.get();
      }
      catch(...)
      {
         except_raised = true;
      }
      UNIT_ASSERT(except_raised, " libmda::util::expected exception was not raised ");
   }
};

} /* namespace util */
} /* namespace tests */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_UTIL_EXPECTED_H_INCLUDED */
