#ifndef LIBMDA_METAPROG_INSERT_H
#define LIBMDA_METAPROG_INSERT_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{
template<class> struct insert_impl;

} // namespace detail

//**  interface at  **//
template<class T, typename U, size_t N>
using insert = typename detail::insert_impl<Tag<T> >::template apply<T,U,N>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_INSERT_H */
