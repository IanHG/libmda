#ifndef LIBMDA_REQUIRE_H_INCLUDED
#define LIBMDA_REQUIRE_H_INCLUDED

#include "../basic_using.h"
#include "../metaprog/std_wrappers.h"

namespace libmda
{
namespace utility
{
namespace detail
{

//template<int N, int M> struct check_order;
//template<int N> struct check_order<N,N> { using type = int; };
//
//template<class A, int N> struct require_order: check_order<A::order,N> { };

//template<>               struct require_order<double,0> { using type = int; }
//{};

}

template<class A, int N>
using Require_order     = iEnable_if<Remove_const<Remove_reference<A> >::order == N>;
//using Require_order     = typename detail::require_order<A,N>::type;

template<class A, int N>
using Require_order_geq = iEnable_if<Remove_const<Remove_reference<A> >::order >= N>;

template<class A, int N>
using Require_order_leq = iEnable_if<Remove_const<Remove_reference<A> >::order <= N>;

} // namespace utility

using utility::Require_order;
using utility::Require_order_geq;
using utility::Require_order_leq;

} // namespace libmda

#endif /* LIBMDA_REQUIRE_H_INCLUDED */
