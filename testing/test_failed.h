#ifndef LIBMDA_TESTING_TEST_FAILED_H_INCLUDED
#define LIBMDA_TESTING_TEST_FAILED_H_INCLUDED

#include<string>
#include<iostream>
#include<sstream>
#include<type_traits>
#include<iomanip>

#include "failed_data.h"
#include "../numeric/float_eq.h"

namespace libmda
{
namespace testing
{
namespace detail
{

template<bool>
struct output_float_dist
{
   template<class T>
   static void apply(std::stringstream& s, const T& got, const T& expected)
   {
      // do nothing
   }
};

// specialization for floating point
template<>
struct output_float_dist<true>
{
   template<class T>
   static void apply(std::stringstream& s, const T& got, const T& expected)
   {
      s << " dist: " << libmda::numeric::float_ulps(expected, got);
   }
};

} /* namespace detail */
                              

//
//
//
struct test_failed
{

   public:
      template<typename T>
      test_failed(const std::string a_name,
                  const char* a_file, 
                  const unsigned int a_line, 
                  const std::string a_what,
                  const T& a_expected,
                  const T& a_got): 
         m_name(a_name), 
         m_file(a_file), m_line(a_line), m_what(a_what), m_message(),
         m_pdata(failed_data_factory(a_expected,a_got))
      { 
         // make this prettier ?? YES !!..
         m_message.append(m_name);
         m_message.append(": ");
         std::stringstream s;
         s << std::boolalpha << std::scientific << std::setprecision(16); 
         s << " expected ";
         m_pdata->expected(s);
         s << " got ";
         m_pdata->got(s);
         detail::output_float_dist<std::is_floating_point<typename std::decay<T>::type>::value>::apply(s, a_got, a_expected);
         m_message.append(" in file ");
         m_message.append(m_file);
         m_message.append(" on line ");
         m_message.append(std::to_string(m_line));
         m_message.append("\n happened: ");
         m_message.append(m_what);
         m_message.append("\n");
         m_message.append(s.str());
      };

      //
      //
      //
      virtual ~test_failed() 
      { 
         failed_data_destroy(m_pdata); 
      }
      
      //
      //
      //
      const char* what() const throw()
      {
         return m_message.c_str();
      }
   
   private:
      const std::string  m_name; // ADD ME !
      const std::string  m_file;
      const unsigned int m_line;
      const std::string  m_what;
      std::string        m_message;
      failed_data_base*  m_pdata;
};

} // namespace testing
} // namespace libmda

#endif // LIBMDA_TESTING_TEST_FAILED_H_INCLUDED
