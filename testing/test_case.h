#ifndef LIBMDA_TESTING_TEST_CASE_H
#define LIBMDA_TESTING_TEST_CASE_H

#include "unit_test.h"
#include "unit_test_factory.h"
#include "test_failed.h"

namespace libmda
{
namespace testing
{

class test_case: virtual protected unit_test_holder, virtual public unit_test
{
   private:
      unsigned int m_num_test;

      void incr_num_test(const unsigned int a_num_test)
      { m_num_test += a_num_test; }
   public:
      test_case(): unit_test_holder(), unit_test(), m_num_test(0) { };
      virtual ~test_case() { }

      void do_test() throw(test_failed)
      {
         for(int i=0; i<test_size(); ++i)
         {
            try
            {
               get_test(i)->do_test();
            }
            catch(test_failed &e)
            {
               cout << "FAILED TEST: " << get_test(i)->name() << endl;
               throw;
            }
            
            incr_num_assertions(get_test(i)->num_assertions());
            incr_num_test(get_test(i)->num_test());
         }
      }

      unsigned int num_test() const { return m_num_test; }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_TEST_CASE_H */
