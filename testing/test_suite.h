#ifndef LIBMDA_TESTING_TEST_SUITE_H
#define LIBMDA_TESTING_TEST_SUITE_H

#include <iostream>

#include "unit_test.h"
#include "unit_test_factory.h"
#include "timer.h"

namespace libmda
{
namespace testing
{

class test_suite: public unit_test_holder
{
   private:
      typedef unsigned int count_type;
      clock_timer m_timer;
      count_type m_assertions;
      count_type m_failed;
      count_type m_num_test;
      
      void end_output(std::ostream& a_ostream)
      {
         a_ostream << "Finished tests in " << m_timer.tot_clocks_per_sec() << "s, "
                   << m_num_test/m_timer.tot_clocks_per_sec() << " tests/s, "
                   << m_assertions/m_timer.tot_clocks_per_sec() << " assertions/s \n"; 
         a_ostream << m_num_test << " tests, "
                   << m_assertions << " assertions, "
                   << m_failed << " failed \n";
      }
   public:
      test_suite(): unit_test_holder(), m_timer(), 
                    m_assertions(0), m_failed(0), m_num_test(0)
      { }
      ~test_suite() { }

      void do_tests(std::ostream& a_ostream = std::cout)
      { 
         m_timer.start();
         for(int i=0; i<test_size(); ++i)
         {
            get_test(i)->setup();    // setup test
            try
            {
               get_test(i)->do_test();
            }
            catch(test_failed &e)
            {
               a_ostream << " FAILED TEST: " << get_test(i)->name() << "\n"
                         << e.what() << std::endl;
               ++m_failed;
            }
            m_assertions+=get_test(i)->num_assertions();
            m_num_test+=get_test(i)->num_test();
            m_failed+=get_test(i)->num_failed(); // for test case (unit test will return 0 no matter)
            get_test(i)->teardown(); // teardown test
         }
         m_timer.stop();
         end_output(a_ostream);
      }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_TEST_SUITE_H */
