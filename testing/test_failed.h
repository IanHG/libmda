#ifndef LIBMDA_TESTING_TEST_FAILED_H
#define LIBMDA_TESTING_TEST_FAILED_H

#include<string>
using std::string;
#include<iostream>
#include<sstream>
using std::stringstream;
using std::ostringstream;

namespace libmda
{
namespace testing
{

struct failed_data_base
{
   public:
      virtual void expected(stringstream&) const = 0;
      virtual void got(stringstream&)      const = 0;

      virtual ~failed_data_base() { };
};

template<typename T>
struct failed_data: public failed_data_base
{
   private:
      const T m_expected;
      const T m_got;
   
   public:
      failed_data(const T& a_expected, const T& a_got):
         m_expected(a_expected), m_got(a_got) { }
      void expected(stringstream& s) const { s << m_expected; }
      void got(stringstream& s)      const { s << m_got; }
};

template<typename T>
failed_data<T>* failed_data_factory(const T& a_expected, const T& a_got)
{ return new failed_data<T>(a_expected,a_got); }

void failed_data_destroy(failed_data_base* a_failed_data)
{ delete a_failed_data; }

struct test_failed
{
   private:
      const string       m_name; // ADD ME !
      const string       m_file;
      const unsigned int m_line;
      const string       m_what;
      string             m_message;
      failed_data_base*  m_pdata;

   public:
      template<typename T>
      test_failed(const string a_name,
                  const char* a_file, 
                  const unsigned int a_line, 
                  const string a_what,
                  const T& a_expected,
                  const T& a_got): 
         m_name(a_name), 
         m_file(a_file), m_line(a_line), m_what(a_what), m_message(),
         m_pdata(failed_data_factory(a_expected,a_got))
      { 
         // make this prettier ?? YES !!..
         m_message.append(m_name);
         m_message.append(": ");
         stringstream s;
         s << " expected ";
         m_pdata->expected(s);
         s << " got ";
         m_pdata->got(s);
         m_message.append(" in file ");
         m_message.append(m_file);
         m_message.append(" on line ");
         m_message.append(std::to_string(m_line));
         m_message.append("\n happened: ");
         m_message.append(m_what);
         m_message.append("\n");
         m_message.append(s.str());
      };

      ~test_failed() { failed_data_destroy(m_pdata); }
      
      //virtual ~test_failed() { };

      const char* what() const throw()
      {
         return m_message.c_str();
      }
};

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_TEST_FAILED_H */
