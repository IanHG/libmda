#ifndef LIBMDA_OP_TENSORPROD_H_INCLUDED
#define LIBMDA_OP_TENSORPROD_H_INCLUDED

#include "../basic_using.h"
#include "expression.h"
#include "../util/forward_pack.h"

namespace libmda
{
namespace expr
{
namespace detail
{

template<class A>
struct tensorprod_helper
{
   private:
      const A& m_a;

   public:
      tensorprod_helper(const A& a_a): m_a(a_a) { };
      
      template<typename... ints> 
      Value_type<A> operator()(ints... i) const { return m_a.at(i...); };
};

} // namespace detail

template<class L, class R>
struct op_tensorprod
{
   static const int order = Order<L>()+Order<R>();

   template<typename... ints>
   static Value_type<L> apply(const L& a_lhs, const R& a_rhs, const ints... i)
   {
      return util::forward_subpack(detail::tensorprod_helper<L>(a_lhs),meta::index_range<0,Order<L>()>(),i...)*
         util::forward_subpack(detail::tensorprod_helper<R>(a_rhs),meta::index_range<Order<L>(),order>(),i...);
   }

   template<int N, iEnable_if< (N>=0 && N<L::order) > = 0>
   static Size_type<L> extent(const L& a_lhs, const R& a_rhs)
   {
      return a_lhs.template extent<N>();
   }
   
   template<int N, iEnable_if< (N>=L::order && N<order) > = 0>
   static Size_type<R> extent(const L& a_lhs, const R& a_rhs)
   {
      return a_rhs.template extent<N-L::order>();
   }

   static Size_type<L> size(const L& a_lhs, const R& a_rhs)
   {
      return a_lhs.size()*a_rhs.size();
   }
};

} // namespace expr

template<class L, class R>
expr::binary_expression<expr::expression_base<L>,expr::expression_base<R>,expr::op_tensorprod> 
tensorprod(const expr::expression_base<L>& a_lhs, const expr::expression_base<R>& a_rhs)
{
   return expr::binary_expression<expr::expression_base<L>,
                     expr::expression_base<R>,expr::op_tensorprod>(a_lhs,a_rhs);
};

} // namespace libmda

#endif /* LIBMDA_OP_TENSORPROD_H_INCLUDED */
