#ifndef LIBMDA_METAPROG_AT_H_INCLUDED
#define LIBMDA_METAPROG_AT_H_INCLUDED

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct at_impl;

} // namespace detail

//
//**  interface at  **//
//
template<class T, size_t N>
using at = typename detail::at_impl<Tag<T> >::template apply<T,N>::type;

} // namespace meta
} // namespace libmda

#endif // LIBMDA_METAPROG_AT_H_INCLUDED
