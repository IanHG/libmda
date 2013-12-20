#ifndef LIBMDA_METAPROG_RANGE_H
#define LIBMDA_METAPROG_RANGE_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{
template<class> struct range_impl;

} // namespace detail

// empty interface
template<class T, int N, int M>
using range = typename detail::range_impl<Tag<T> >::template apply<T,N,M>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_RANGE_H */
