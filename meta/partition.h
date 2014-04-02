#ifndef LIBMDA_METAPROG_PARTITION_H
#define LIBMDA_METAPROG_PARTITION_H

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct partition_impl;

} // namespace detail

// interface
// Pred: must be a class that provides an internal apply class,
//       that takes a single template argument, and has an internal value
template<class T, class Pred>
using partition = typename detail::partition_impl<Tag<T> >::template apply<T,Pred>;

// partition true types
template<class T, class Pred>
using partition_t = typename partition<T,Pred>::t;
// partition false types
template<class T, class Pred>
using partition_f = typename partition<T,Pred>::f;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_PARTITION_H */
