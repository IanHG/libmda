#ifndef LIBMDA_TESTING_PERFORMANCE_TEST_H
#define LIBMDA_TESTING_PERFORMANCE_TEST_H

//#include<typeinfo>
#include<iostream>
using std::cout;
using std::endl;

#include "test_failed.h"
#include "timer.h"

namespace libmda
{
namespace testing
{

template<size_t repeats, typename test>
class performance_test: 
   public virtual unit_test,
   private virtual test // using inheritance for EBCO (empty base class optimization)
{
   private:
      clock_timer m_timer;

      void benchmark_output() const
      {
         cout << " TEST: " << name() << endl;
         cout << " did "   << repeats << " runs and "
              << " used: " << m_timer.tot_clocks() << " clocks "
              << " (in "   << m_timer.tot_clocks_per_sec() << "s)."
              << endl;
      }
   public:
      template<typename... Args>
      performance_test(const string a_name, const Args&... args): 
         unit_test(), test(a_name,args...), m_timer()
      { }

      void do_test() throw(test_failed)
      { 
         m_timer.start();
         //test::setup();  // setup test (done by test_suite)
         //for(int i=0; i<repeats; ++i) // loop over repeats
         //{
         //   try
         //   {
               for(size_t i=0; i<repeats; ++i) // loop over repeats
                  test::do_test(); // run the test
         //   }
         //   catch(test_failed &e) // catch any test_failed
         //   {
         //      cout << " there was an error in performance test: " << "\n" //i << "\n"
         //           << " rethrowing to test_suite handler..." << endl;
         //      throw;
         //   }
         //}
         //test::teardown(); // teardown test
         m_timer.stop();
         benchmark_output();
      }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_PERFORMANCE_TEST_H */
