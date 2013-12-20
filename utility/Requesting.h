#ifndef LIBMDA_REQUESTING_H
#define LIBMDA_REQUESTING_H

//#include "../expr/char_expression.h"
#include "../metaprog/std_wrappers.h"
#include "../metaprog/check_type_.h"
#include "../expr/check_cindicies.h"
#include "../basic_using.h"

namespace libmda
{
namespace utility
{
namespace detail
{

//template<class A, typename... Args>
//struct requesting_elem
//{
//   static const bool value = (sizeof...(Args) == Order<A>() 
//         && All(Convertible<Remove_const<Remove_reference<Args> >,Size_type<A> >()...));
//};

template<int N, typename size_type, typename... Args>
struct requesting_elem
{
   //static const bool value = (sizeof...(Args) == N
   //      && All(Convertible<Remove_const<Remove_reference<Args> >, size_type>()...));
   static const bool value = (sizeof...(Args) == N) 
      && metaprog::check_type_and_size_<N,size_type,Args...>::value;
};

template<int N, typename... Args>
struct requesting_slice
{
   static const bool value = ((sizeof...(Args) == N) 
         && char_expr::check_cindicies_<Args...>::value);
};

} // namespace detail

template<int N, typename size_type, typename... Args>
using Requesting_elem  = iEnable_if<detail::requesting_elem<N,size_type,Args...>::value>;

template<int N, typename... Args>
using Requesting_slice = iEnable_if<detail::requesting_slice<N,Args...>::value>;

} // namespace utility

} // namespace libmda

#endif /* LIBMDA_REQUESTING_H */
