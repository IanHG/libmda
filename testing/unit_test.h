#ifndef LIBMDA_TESTING_UNIT_TEST_H
#define LIBMDA_TESTING_UNIT_TEST_H

#include<string>

#include"test_failed.h"
#include"unit_assert.h"

namespace libmda
{
namespace testing
{


class unit_test
{
      using count_type = unsigned int;

   public:
      //
      // constructor
      //
      unit_test(): m_num_assertions(0) 
      { 
      }
      
      //
      // virtual destructor
      //
      virtual ~unit_test() 
      { 
      }
      
      //
      // overloadable function for doing the actual test
      //
      virtual void do_test() = 0;
      
      //
      // overloadable function for optional setup test method
      //
      virtual void setup()    
      { 
      }
      
      //
      // overloadable function for optional teardown test method
      //
      virtual void teardown() 
      { 
      }
      
      //
      // 
      //
      void incr_num_assertions(int a_incr=1)
      { 
         m_num_assertions+=a_incr; 
      }
      
      //
      // 
      //
      count_type num_assertions() const
      { 
         return m_num_assertions; 
      }
      
      //
      // overloadable function for returning the number of tests
      //
      virtual unsigned num_test() const 
      { 
         return 1; 
      }

      //
      // 
      //
      virtual unsigned num_failed() const
      {
         return 0;
      }
      
      //
      // interface function for getting name of test
      //
      virtual std::string name() const = 0;
   
   private:
      count_type m_num_assertions;
};

template<class A>
class unit_test_name: public A
{
   public:
      template<typename... Args>
      unit_test_name(const std::string a_name, Args... args): A(args...)
                                                            , m_name(a_name) 
      { 
      }

      std::string name() const 
      { 
         return m_name; 
      }
   
   private:
      const std::string m_name;
};

class default_test_name
{
   public:
      static std::string acquire_name()
      { 
         ++m_num; 
         return m_name+"_"+std::to_string(m_num); 
      }
   
   private:
      static std::string  m_name;
      static unsigned int m_num;
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_UNIT_TEST_H */
