#ifndef LIBMDA_MDA_EXPRESSION_H_INCLUDED
#define LIBMDA_MDA_EXPRESSION_H_INCLUDED

#include "expression_base.h"

namespace libmda
{
namespace expr
{

template<class A>
struct mda_expression: expression_base<A>
{
   public:
      using expression_base<A>::expression_type;
      using tag_type = mda_tag;

      using value_type = typename A::value_type;
      using size_type = typename A::size_type;
      //using A::order;
      //
      A& operator()()
      {
         return static_cast<A&>(*this);
      }

      const A& operator()() const
      {
         return static_cast<const A&>(*this);
      }

   protected:
      mda_expression() = default;
      ~mda_expression() {};

   private:
      mda_expression(const mda_expression<A>&) = delete;
      mda_expression<A>& operator=(const mda_expression<A>&) = delete;
};

//template<class A>
//struct mda_reference: mda_expression<A>
//{
//   public:
//      mda_reference(const A& mda): mda_(mda)
//      {
//      }
//
//      template<class B>
//      mda_reference& operator=(const mda_expression<B>& other)
//      {
//
//         return *this;
//      }
//   
//   private:
//      mda_reference() = delete;
//      mda_reference(const mda_reference&) = delete;
//      mda_reference& operator=(const mda_reference&) = delete;
//
//      const A& mda_;
//}

} /* namespace expr */
} /* namespace libmda */

#endif /* LIBMDA_MDA_EXPRESSION_H_INCLUDED */
