#ifndef LIBMDA_METAPROG_PUSH_FRONT_H
#define LIBMDA_METAPROG_PUSH_FRONT_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{

template<class> struct push_front_impl;

} // namespace detail

// empty interface
template<class T, class... U>
using push_front = typename detail::push_front_impl<Tag<T> >::template apply<T,U...>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_PUSH_FRONT_H */
