#ifndef LIBMDA_METAPROG_CATENATE_H
#define LIBMDA_METAPROG_CATENATE_H

#include "std_wrappers.h"
#include "tag.h"
#include "id.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class> struct catenate_impl;

//
// indirection to check that types are the same
//
template<class T, class U> 
struct catenate_check: catenate_impl<Tag<T> > 
{
   static_assert(Is_same<Tag<T>, Tag<U> >(), "catenate error: not same type");
};

//
// indirection to allow catenation of multiple args
//
template<class... Ts>
struct catenate_;

template<class T, class U, class... Us>
struct catenate_<T,U,Us...>: catenate_<typename catenate_<T,U>::type,Us...>
{
};

template<class T, class U>
struct catenate_<T,U>: catenate_check<T,U>::template apply<T,U>
{
};

template<class T>
struct catenate_<T>: id<T>
{
};

} /* namespace detail */

//
// catenate interface
//
template<class... Ts>
using catenate = typename detail::catenate_<Ts...>::type;
//using catenate = typename detail::catenate_check<T,U>::template apply<T,U>::type;

} /* namespace meta */
} /* namespace libmda */

#endif /* LIBMDA_METAPROG_CATENATE_H */
