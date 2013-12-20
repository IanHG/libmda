#ifndef LIBMDA_METAPROG_AT_H
#define LIBMDA_METAPROG_AT_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{
template<class> struct at_impl;

} // namespace detail

//**  interface at  **//
template<class T, size_t N>
using at = typename detail::at_impl<Tag<T> >::template apply<T,N>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_AT_H */
