#ifndef LIBMDA_METAPROG_POP_BACK_H
#define LIBMDA_METAPROG_POP_BACK_H

#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{

template<class> struct pop_back_impl;

} // namespace detail

// empty interface
template<class T>
using pop_back = typename detail::pop_back_impl<Tag<T> >::template apply<T>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_POP_BACK_H */
