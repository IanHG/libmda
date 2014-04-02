#ifndef LIMBDA_TESTING_UNIT_TEST_FACTORY_H_INCLUDED
#define LIMBDA_TESTING_UNIT_TEST_FACTORY_H_INCLUDED

#include <string>
#include <vector>

#include "unit_test.h"
#include "performance_test.h"

namespace libmda
{
namespace testing
{

//
//
//
template<class T, typename... Args>
unit_test* unit_test_factory(const std::string a_name, const Args&... args)
{
   //return new T(args...);
   return new unit_test_name<T>(a_name, args...);
}

//
//
//
template<class T, int N, typename... Args>
unit_test* performance_test_factory(const std::string a_name, const Args&... args)
{
   return new performance_test<N,unit_test_name<T> >(a_name, args...);
}

//
//
//
template<class T>
void unit_test_destroy(T* ptr)
{
   delete ptr;
}

//
//
//
class unit_test_holder
{
   public:
      //
      // virtual destructor
      //
      virtual ~unit_test_holder()
      { 
         for(int i=0; i<m_tests.size(); ++i) 
            unit_test_destroy(m_tests[i]); 
      }

      //
      // add tests (T is test class type) with name defaulted to default-name
      //
      template<class T>
      void add_test(const std::string a_name=default_test_name::acquire_name())
      { 
         m_tests.push_back(unit_test_factory<T>(a_name)); 
      }
      
      //
      // add test with extra arguments
      //
      template<class T, typename... Args>
      void add_test(const std::string a_name, const Args&... args)
      { 
         m_tests.push_back(unit_test_factory<T>(a_name, args...)); 
      }
      
      //
      // add performance tests (N is num runs, T is test class type)
      //
      template<int N, class T>
      void add_performance_test(const std::string a_name=default_test_name::acquire_name())
      { 
         m_tests.push_back(performance_test_factory<T,N>(a_name)); 
      }
                              
      //
      // add performance tests (N is num runs, T is test class type)
      //
      template<int N, class T, typename... Args>
      void add_performance_test(const std::string a_name, const Args&... args)
      { 
         m_tests.push_back(performance_test_factory<T,N>(a_name,args...)); 
      }
      
      //
      // get test number i
      //
      unit_test* get_test(int i) 
      { 
         return m_tests[i]; 
      }
      
      //
      // get number of tests
      //
      int test_size() const 
      { 
         return m_tests.size(); 
      }
   
   private:
      std::vector<unit_test*> m_tests;
};

} // namespace testing
} // namespace libmda

#endif // LIMBDA_TESTING_UNIT_TEST_FACTORY_H_INCLUDED
