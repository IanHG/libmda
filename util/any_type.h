#ifndef LIBMDA_UTIL_ANY_TYPE_H_INCLUDED
#define LIBMDA_UTIL_ANY_TYPE_H_INCLUDED

#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <stdexcept>

namespace libmda
{
namespace util
{
namespace detail
{
/**
 *
 **/
class any_type_base
{
   public:
      /**
       *
       **/
      any_type_base() = default;

      /**
       *
       **/
      virtual any_type_base* clone() const = 0;

   private:
};

/**
 *
 **/
template<class T>
class any_type_explicit
   : public any_type_base
{
   public:
      /**
       *
       **/
      any_type_explicit(const T& t)
         : m_data(t)
      {
      }
      
      /**
       *
       **/
      any_type_explicit(T&& t)
         : m_data(std::move(t))
      {
      }

      /**
       *
       **/
      any_type_explicit<T>* clone() const override
      {
         return new any_type_explicit<T>(*this);
      }
      
      /**
       *
       **/
      const T& get() const
      {
         return m_data;
      }
      
      /**
       *
       **/
      T& get()
      {
         return m_data;
      }

   private:
      /**
       *
       **/
      T m_data;
};

} /* namespace detail */

/**
 *
 **/
class any_type
{
   public:
      using type_index = std::type_index;

      /**
       *
       **/
      any_type()
         : m_data(nullptr)
         , m_type(typeid(nullptr))
      {
      }
      
      /**
       *
       **/
      template< class T
              , class T_decayed = typename std::decay<T>::type
              , typename std::enable_if<!std::is_same<T_decayed,any_type>::value>::type* = nullptr 
              >
      any_type(T&& t)
         : m_data(new detail::any_type_explicit<T_decayed>(std::forward<T>(t)))
         , m_type(typeid(T_decayed))
      {
      }

      /**
       *
       **/
      any_type(const any_type& at)
         : m_data(at.m_data->clone())
         , m_type(at.m_type)
      {
      }
      
      /**
       *
       **/
      any_type(any_type&& at)
         : m_data(nullptr)
         , m_type(typeid(nullptr))
      {
         std::swap(m_data, at.m_data);
         std::swap(m_type, at.m_type);
      }

      /**
       *
       **/
      ~any_type()
      {
         if(m_data)
            delete m_data;
      }

      /**
       *
       **/
      any_type& operator=(const any_type& at)
      {
         if(this != &at)
         {
            //if(m_type == at.m_type)
            //{
            //   
            //}
            //else
            {
               if(m_data)
                  delete m_data;
               m_data = at.m_data->clone();
               m_type = at.m_type;
            }
         }

         return *this;
      }

      /**
       *
       **/
      any_type& operator=(any_type&& at)
      {
         std::swap(m_data, at.m_data);
         std::swap(m_type, at.m_type);
         return *this;
      }

      
      /**
       *
       **/
      template<class T
             , class T_decayed = typename std::decay<T>::type
             , typename std::enable_if<!std::is_same<T_decayed,any_type>::value>::type* = nullptr
             >
      any_type& operator=(T&& t)
      {
         if(m_type == type_index(typeid(T)))
         {
            static_cast<detail::any_type_explicit<T_decayed>*>(m_data)->get() = std::forward<T>(t);
         }
         else
         {
            if(m_data)
               delete m_data;
            m_data = new detail::any_type_explicit<T_decayed>(std::forward<T>(t));
            m_type = type_index(typeid(T_decayed));
         }
      }

      
      /**
       *
       **/
      template<class T>
      const T& get() const
      {
         assert_type_index<T>();
         return static_cast<const detail::any_type_explicit<T>*>(m_data)->get();
      }
      
      /**
       *
       **/
      template<class T>
      T& get()
      {
         assert_type_index<T>();
         return static_cast<detail::any_type_explicit<T>*>(m_data)->get();
      }

      /**
       *
       **/
      const type_index& type() const
      {
         return m_type;
      }
      
      /**
       *
       **/
      std::string type_name() const
      {
         return std::string(m_type.name());
      }

   private:
      /**
       * 
       **/
      template<class T>
      void assert_type_index() const
      {
         if(type_index(typeid(T)) != m_type)
            throw std::runtime_error("bad cast: trying get type '" + std::string(typeid(T).name()) + "' from 'any_type<" + m_type.name() + ">'");
      }
      
      /**
       *
       **/
      detail::any_type_base* m_data;
      /**
       *
       **/
      type_index m_type;
};

// relational operators
inline bool operator<(const any_type& a1, const any_type& a2)
{
   return a1.type() < a2.type();
}

// output operator
inline std::ostream& operator<<(std::ostream& os, const any_type& a)
{
   if(a.type() == any_type::type_index(typeid(double)))
   {
      os << " any_type: type = double, value = " << a.get<double>();
   }
   else if(a.type() == any_type::type_index(typeid(int)))
   {
      os << " any_type: type = int, value = " << a.get<int>();
   }
   else if(a.type() == any_type::type_index(typeid(std::string)))
   {
      os << " any_type: type = std::string, value = " << a.get<std::string>();
   }
   else
   {
      os << " any_type: operator<< not implemented for type = " << a.type_name();
   }
   return os;
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_ANY_TYPE_H_INCLUDED */
