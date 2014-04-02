#ifndef LIBMDA_METAPROG_REMOVE_H
#define LIBMDA_METAPROG_REMOVE_H

#include "tag.h"
#include "remove_if.h"
#include "same_as.h"

namespace libmda
{
namespace meta
{
namespace detail
{
  // no details for remove... this is implemented in terms of remove_if
} // namespace detail


// remove interface
template<class T, typename U>
using remove = typename detail::remove_if_impl<Tag<T> >::template apply<T,same_as<U> >::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_POP_FRONT_H */
