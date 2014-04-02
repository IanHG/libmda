#ifndef LIBMDA_TESTING_FAILED_DATA_H_INCLUDED
#define LIBMDA_TESTING_FAILED_DATA_H_INCLUDED

#include<string>
#include<iostream>
#include<sstream>

namespace libmda
{
namespace testing
{

//
//
//
struct failed_data_base
{
   public:
      virtual void expected(std::stringstream&) const = 0;
      virtual void got(std::stringstream&)      const = 0;

      virtual ~failed_data_base() 
      { 
      }
};

//
//
//
template<typename T>
struct failed_data: public failed_data_base
{
   public:
      failed_data(const T& a_expected, const T& a_got):
         m_expected(a_expected), m_got(a_got) 
      { 
      }

      void expected(std::stringstream& s) const 
      { 
         s << m_expected; 
      }

      void got(std::stringstream& s)      const 
      { 
         s << m_got; 
      }
   
   private:
      const T m_expected;
      const T m_got;
};

//
//
//
template<typename T>
failed_data<T>* failed_data_factory(const T& a_expected, const T& a_got)
{ 
   return new failed_data<T>(a_expected,a_got); 
}

//
//
//
void failed_data_destroy(failed_data_base* a_failed_data);

} // namespace testing
} // namespace libmda

#endif // LIBMDA_TESTING_TEST_FAILED_H_INCLUDED
