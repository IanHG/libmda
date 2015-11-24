#ifndef LIBMDA_TESTS_UTIL_SCOPE_GUARD_H_INCLUDED
#define LIBMDA_TESTS_UTIL_SCOPE_GUARD_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>
#include<limits>   // for std::numeric_limits
#include <type_traits>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/scope_guard.h"

namespace libmda
{
namespace tests
{
namespace util
{

/**
 *
 **/
struct scope_guard_run_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      int i = 0;
      {
         auto g = libmda::util::make_scope_guard([&i](){ i = 2; });
      }
      UNIT_ASSERT_EQUAL(i, 2, " libmda::util::scope_guard run failed ");
   }
};

/**
 *
 **/
struct scope_guard_dismiss_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      int i = 0;
      {
         auto g = libmda::util::make_scope_guard([&i](){ i = 2; });
         g.dismiss();
      }
      UNIT_ASSERT_EQUAL(i, 0, " libmda::util::scope_guard dismiss failed ");
   }
};

/**
 *
 **/
struct scope_guard_macro_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      int i = 0;
      {
         scope_exit_do([&i](){ i = 2; });
      }
      UNIT_ASSERT_EQUAL(i, 2, " libmda::util::scope_guard run failed ");
   }
};

} /* namespace util */
} /* namespace tests */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_UTIL_SCOPE_GUARD_H_INCLUDED */
