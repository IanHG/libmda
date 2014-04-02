#ifndef LIBMDA_METAPROG_POP_FRONT_H
#define LIBMDA_METAPROG_POP_FRONT_H

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct pop_front_impl;

} // namespace detail

// empty interface
template<class T>
using pop_front = typename detail::pop_front_impl<Tag<T> >::template apply<T>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_POP_FRONT_H */
