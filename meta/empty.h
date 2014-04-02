#ifndef LIBMDA_METAPROG_EMPTY_H
#define LIBMDA_METAPROG_EMPTY_H

#include "std_wrappers.h"
#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct empty_impl;

} // namespace detail

// empty interface
template<class T>
using empty = typename detail::empty_impl<Tag<T> >::template apply<T>::type;

template<class T>
constexpr bool Is_empty()
{
   return Is_same<T,empty<T> >();
}

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_EMPTY_H */
