#ifndef LIBMDA_METAPROG_PERMUTE_H
#define LIBMDA_METAPROG_PERMUTE_H

#include "mpsize_t.h"
#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class T> struct permute_impl;

} // namespace detail

template<class T, class U> 
using permute = typename detail::permute_impl<Tag<T> >::template apply<T,U>::type;

template<class... N> class permutation_;
template<class T, size_t... N> 
using i_permute = typename detail::permute_impl<Tag<T> >::template apply<T,permutation_<mpsize_t<N>...> >::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_PERMUTE_H */
