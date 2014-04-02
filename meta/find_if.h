#ifndef LIBMDA_METAPROG_FIND_IF_H
#define LIBMDA_METAPROG_FIND_IF_H

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{
template<class> struct find_if_impl;

} // namespace detail

//**  find_if  **//
// unaryPredicate: must be a class that provides an internal apply class,
//                 that takes a single template argument, and has an internal value
//
//       e.g.  template<class T> struct someUnaryPredicate
//             {
//                template<class U> struct apply
//                {
//                   static const bool value = /* some computation based on T and U */
//                };
//             };
//
//
template<class T, class unaryPredicate> 
using find_if = typename detail::find_if_impl<Tag<T> >::template apply<T,unaryPredicate>::type;

//template<class T, typename U> 
//constexpr size_t Find() { return find<T,U>::value; }

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_FIND_IF_H */
