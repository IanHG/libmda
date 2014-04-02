#ifndef LIBMDA_META_SIZE_H_INCLUDED
#define LIBMDA_META_SIZE_H_INCLUDED

#include "tag.h"

namespace libmda
{
namespace meta
{
namespace detail
{

//
//
//
template<class> struct size_impl;

//
//
//
template<size_t N> 
struct size_cont
{
   static const size_t value = N;
};


} // namespace detail

//
//**  interface at  **//
//
template<class T>
using size = typename detail::size_impl<Tag<T> >::template apply<T>::type;

template<class T>
constexpr auto Size()
   -> decltype(size<T>::value)
{
   return size<T>::value;
}

} // namespace meta
} // namespace libmda

#endif // LIBMDA_META_SIZE_H_INCLUDED
