#ifndef LIBMDA_SCALAR_EXPRESSION_H_INCLUDED
#define LIBMDA_SCALAR_EXPRESSION_H_INCLUDED

#include "expression_base.h"

namespace libmda
{
namespace expr
{

////
//
////
template<class A>
struct scalar_expression: expression_base<A>
{
   public:
      using expression_type = typename expression_base<A>::expression_type;
      using tag_type = scalar_tag;
      
      static const unsigned order = 0;
      //using value_type = typename A::value_type;

      expression_type& operator()() 
      {
         return static_cast<expression_type&>(*this);
      }
      
      const expression_type& operator()() const
      {
         return static_cast<const expression_type&>(*this);
      }

   protected:
      scalar_expression() = default;
      ~scalar_expression() {};

   private:
      scalar_expression(const scalar_expression<A>&) = delete;
      scalar_expression<A>& operator=(const scalar_expression<A>&) = delete;
};

////
//
////
template<class T>
struct scalar_value: scalar_expression<scalar_value<T> >
{
   public:
      using value_type = T;   
   
      scalar_value(): t_() {};
      scalar_value(value_type&& t): t_(std::move(t)) {};
      ~scalar_value() {};
      
      operator value_type() const
      {
         return t_;
      }

      value_type* operator&()
      {
         return &t_;
      }

      scalar_value<T>& operator=(const value_type& t)
      {
         t_ = t;
         return *this;
      }

      scalar_value<T>& operator=(const scalar_expression<T>& t)
      {
         t_ = t;
         return *this;
      }

   private:
      //scalar_value() = delete;

      value_type t_;
};

////
//
////
template<class T>
struct scalar_reference: scalar_expression<scalar_reference<T> >
{
   public:
      using value_type = T;

      scalar_reference(T& t): t_(t) {};
      ~scalar_reference() {};
      
      operator value_type() const
      {
         return t_;
      }

      scalar_reference<T>& operator=(const value_type& t)
      {
         t_ = t;
         return *this;
      }

      template<class A>
      scalar_reference<T>& operator=(const scalar_expression<A>& t)
      {
         t_ = t();
         return *this;
      }

   private:
      scalar_reference() = delete;

      value_type& t_;
};

} /* namespace expr */
} /* namespace libmda */

#endif /* LIBMDA_SCALAR_EXPRESSION_H_INCLUDED */
