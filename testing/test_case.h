#ifndef LIBMDA_TESTING_TEST_CASE_H
#define LIBMDA_TESTING_TEST_CASE_H

#include <iostream>

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
      unsigned m_num_test;
      unsigned m_failed;

      void incr_num_test(const unsigned int a_num_test)
      { 
         m_num_test += a_num_test; 
      }

   public:
      //
      //
      //
      test_case(): 
         unit_test_holder(), unit_test(), m_num_test(0), m_failed(0)
      { 
      }
      
      //
      //
      //
      virtual ~test_case() 
      { 
      }
      
      //
      //
      //
      void do_test()
      {
         for(int i=0; i<test_size(); ++i)
         {
            try
            {
               get_test(i)->do_test();
            }
            catch(test_failed &e)
            {
               std::cout << "FAILED TEST: " << get_test(i)->name() << "\n"
                         << e.what() << std::endl;
               ++m_failed;
               //throw;
            }
            
            incr_num_assertions(get_test(i)->num_assertions());
            incr_num_test(get_test(i)->num_test());
         }
      }
      
      //
      //
      //
      unsigned num_test() const 
      { 
         return m_num_test; 
      }

      //
      //
      //
      unsigned num_failed() const
      {
         return m_failed;
      }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_TEST_CASE_H */
