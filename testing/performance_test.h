#ifndef LIBMDA_TESTING_PERFORMANCE_TEST_H_INCLUDED
#define LIBMDA_TESTING_PERFORMANCE_TEST_H_INCLUDED

//#include<typeinfo>
#include<iostream>

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

      void benchmark_output(std::ostream& a_stream = std::cout) const
      {
         a_stream << " TEST: " << name() << "\n"
                  << " did "   << repeats << " runs and "
                  << " used: " << m_timer.tot_clocks() << " clocks "
                  << " (in "   << m_timer.tot_clocks_per_sec() << "s)."
                  << std::endl;
      }
   public:
      template<typename... Args>
      performance_test(const std::string a_name, const Args&... args): 
         unit_test(), test(a_name,args...), m_timer()
      { }

      void do_test()
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
         //      std::cout << " there was an error in performance test: " << "\n" //i << "\n"
         //           << " rethrowing to test_suite handler..." << std::endl;
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

#endif // LIBMDA_TESTING_PERFORMANCE_TEST_H_INCLUDED
