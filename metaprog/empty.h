#ifndef LIBMDA_METAPROG_EMPTY_H
#define LIBMDA_METAPROG_EMPTY_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{
template<class> struct empty_impl;

} // namespace detail

// empty interface
template<class T>
using empty = typename detail::empty_impl<Tag<T> >::template apply<T>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_EMPTY_H */
