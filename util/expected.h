#ifndef LIBMDA_UTIL_EXPECTED_H_INCLUDED
#define LIBMDA_UTIL_EXPECTED_H_INCLUDED

#include <iostream>
#include <exception>

namespace libmda
{
namespace util
{

/**
 * @class expected
 *    class for doing stuff :D
 **/
template<class T>
class expected
{
   private:
      union 
      {
         T m_value;
         std::exception_ptr m_except;
      };
      bool m_has_value;
      
      /**
       * 
       **/
      expected() 
      {
      }

   public:
      /**
       *
       **/
      expected(const T& t)
         : m_value(t)
         , m_has_value(true)
      {
      }

      /**
       *
       **/
      expected(T&& t)
         : m_value(std::move(t))
         , m_has_value(true)
      {
      }

      /**
       *
       **/
      expected(const expected<T>& e)
         : m_has_value(e.m_has_value)
      {
         if(m_has_value)
         {
            new (&m_value) T(e.m_value);
         }
         else
         {
            new (&m_except)  std::exception_ptr(e.m_except);
         }
      }

      /**
       *
       **/
      expected(expected<T>&& e)
         : m_has_value(e.m_has_value)
      {
         if(m_has_value)
         {
            new (&m_value) T(std::move(e.m_value));
         }
         else
         {
            new (&m_except)  std::exception_ptr(std::move(e.m_except));
            e.m_except = nullptr;
         }
      }

      /**
       *
       **/
      ~expected()
      {
         if(!m_has_value)
         {
            using std::exception_ptr;
            m_except.~exception_ptr();
         }
         else
         {
            m_value.~T();
         }
      }

      /**
       *
       **/
      expected<T>& operator=(const expected<T>& e)
      {
         this->m_has_value = e.m_has_value;
         if(m_has_value)
         {
            m_value.~T();
            new (&m_value) T(e.m_value);
         }
         else
         {
            using std::exception_ptr;
            m_except.~exception_ptr();
            new (&m_except)  std::exception_ptr(e.m_except);
         }
         return *this;
      }

      /**
       *
       **/
      expected<T>& operator=(expected<T>&& e)
      {
         std::swap(this->m_has_value, e.m_has_value);
         if(m_has_value)
         {
            using std::swap;
            swap(this->m_value, e.m_value);
         }
         else
         {
            std::swap(this->m_except, e.m_except);  
         }
         return *this;
      }
      
      /**
       *
       **/
      static expected<T> from_exception(std::exception_ptr ptr)
      {
         expected<T> e;
         new (&e.m_except) std::exception_ptr(std::move(ptr));
         e.m_has_value = false;
         return e;
      }

      /**
       *
       **/
      template<class U>
      static expected<T> from_exception(U&& u)
      {
         return from_exception(std::make_exception_ptr(std::forward<U>(u)));
      }

      /**
       *
       **/
      bool has_value() const
      {
         return m_has_value;
      }

      /**
       *
       **/
      T& get()
      {
         if(!m_has_value)
         {
            std::rethrow_exception(m_except);
         }
         return m_value;
      }
      
      /**
       *
       **/
      const T& get() const
      {
         if(!m_has_value)
         {
            std::rethrow_exception(m_except);
         }
         return m_value;
      }
};

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_EXPECTED_H_INCLUDED */
