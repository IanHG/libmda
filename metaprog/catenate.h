#ifndef LIBMDA_METAPROG_CATENATE_H
#define LIBMDA_METAPROG_CATENATE_H

#include "../metaprog/std_wrappers.h"
#include "tag.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{

template<class> struct catenate_impl;

// indirection to check that types are the same
template<class T, class U> struct catenate_: catenate_impl<Tag<T> > 
{
   static_assert(Is_same<Tag<T>, Tag<U> >(), "catenate error: not same type");
};

} // namespace detail

// catenate interface
template<class T, class U>
using catenate = typename detail::catenate_<T,U>::template apply<T,U>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_CATENATE_H */
