#ifndef LIBMDA_META_PRODUCT_H_INCLUDED
#define LIBMDA_META_PRODUCT_H_INCLUDED

#include "id.h"

namespace libmda
{
namespace meta
{


namespace detail
{


//
// helper to get return type of product
//
template<class... Ts>
struct product_type;

template<class T>
struct product_type<T>:
   id<T>
{
};

template<class T, class U, class... Ps>
struct product_type<T,U,Ps...>: 
   id<decltype(std::declval<T>() * std::declval<typename product_type<U,Ps...>::type>())>
{
};


} // namespace detail

//
//
//
template<class T>
constexpr T Product(T t)
{
   return t;
}

//
// 
//
template<class T, class... Ts>
constexpr auto Product(T t, Ts... ts)
   -> decltype(std::declval<T>()*std::declval<typename detail::product_type<Ts...>::type>())
{
   return t * Product(std::forward<Ts>(ts)...);
}

} // namespace meta
} // namespace libmda

#endif // LIBMDA_META_PRODUCT_H_INCLUDED
