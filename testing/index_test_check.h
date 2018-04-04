#ifndef LIBMDA_TESTING_INDEX_TEST_CHECK_H
#define LIBMDA_TESTING_INDEX_TEST_CHECK_H

#include "test_failed.h"
#include "unit_test.h"

namespace libmda
{
namespace testing
{

struct index_test_check
{
   template<typename T, typename U>
   static void apply(const T index1, const U index2)
   { 
      ASSERT(index1>=0, " index is negative ");
      ASSERT(index1<index2, " index has overcounted ");
   }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_INDEX_TEST_CHECK_H */
