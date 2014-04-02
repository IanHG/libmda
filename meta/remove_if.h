#ifndef LIBMDA_METAPROG_REMOVE_IF_H
#define LIBMDA_METAPROG_REMOVE_IF_H

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct remove_if_impl;

} // namespace detail

// interface
// Pred: must be a class that provides an internal apply class,
//       that takes a single template argument, and has an internal value
//
//       e.g.  template<class T> struct somePredicate_
//             {
//                template<class U> struct apply
//                {
//                   static const bool value = /* some computation based on T and U */
//                };
//             };
//
//
// remove_if loops through T and removes all elements that satisfy the predicate
//
template<class T, class Pred>
using remove_if = typename detail::remove_if_impl<Tag<T> >::template apply<T,Pred>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_REMOVE_IF_H */
