#ifndef LIBMDA_METAPROG_FIND_H
#define LIBMDA_METAPROG_FIND_H

#include "tag.h"
#include "find_if.h"
#include "same_as.h"

namespace libmda
{
namespace meta
{
namespace detail
{
  // no detail as of now... find is implemented in terms of find_if
} // namespace detail

//**  interface find  **//
template<class T, typename U> 
using find = typename detail::find_if_impl<Tag<T> >::template apply<T,same_as<U> >::type;

template<class T, typename U> 
constexpr size_t Find_pos() { return find<T,U>::pos::value; }

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_FIND_H */
