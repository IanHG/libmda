#ifndef LIBMDA_UTIL_ENFORCE_H_INCLUDED
#define LIBMDA_UTIL_ENFORCE_H_INCLUDED

#include "../meta/std_wrappers.h"
#include "../basic_using.h"

namespace libmda
{
namespace util
{
namespace detail
{

template<bool B, class T>
struct enforce_if
{
   static_assert(B, "Requirement not met");
   using type = T;
};

}

template<bool B>
using iEnforce = typename detail::enforce_if<B,int>::type;

template<class A, int N>
using Enforce_order     = iEnforce<Remove_const<Remove_reference<A> >::order == N>;

template<class A, int N>
using Enforce_order_geq = iEnforce<Remove_const<Remove_reference<A> >::order >= N>;

template<class A, int N>
using Enforce_order_leq = iEnforce<Remove_const<Remove_reference<A> >::order <= N>;

template<class A, int N>
using Enforce_order_bound = iEnforce<N < Remove_const<Remove_reference<A> >::order && N >= 0>;

} // namespace util

using util::Enforce_order;
using util::Enforce_order_geq;
using util::Enforce_order_leq;

} // namespace libmda

#endif /* LIBMDA_UTIL_ENFORCE_H_INCLUDED */
