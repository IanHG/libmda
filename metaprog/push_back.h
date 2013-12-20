#ifndef LIBMDA_METAPROG_PUSH_BACK_H
#define LIBMDA_METAPROG_PUSH_BACK_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{

template<class> struct push_back_impl;

} // namespace detail

// empty interface
template<class T, class... U>
using push_back = typename detail::push_back_impl<Tag<T> >::template apply<T,U...>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_PUSH_BACK_H */
