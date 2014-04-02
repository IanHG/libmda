#ifndef LIBMDA_METAPROG_SORT_H
#define LIBMDA_METAPROG_SORT_H

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

//
// a predicate wrapper to do a quicksort
// 
template<class T, class binaryPredicate>
struct QuicksortPred
{
   template<class U> struct apply: binaryPredicate::template apply<T,U>
   {
   };
};

template<class> 
struct sort_impl;

} // namespace detail

//**  sort  **//
// binaryPredicate: must be a class that provides an internal apply class,
//                 that takes two template argument, and has an internal value
//                 value must be true if T should go to the left of/before U
//
//       e.g.  struct someBinaryPredicate
//             {
//                template<class T, class U> struct apply
//                {
//                   static const bool value = /* some computation based on T and U */
//                };
//             };
//
//
template<class T, class binaryPredicate> 
using sort = typename detail::sort_impl<Tag<T> >::template apply<T,binaryPredicate>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_SORT_H */
