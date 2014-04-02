#ifndef LIBMDA_META_SUM_H_INCLUDED
#define LIBMDA_META_SUM_H_INCLUDED

#include "id.h"

namespace libmda
{
namespace meta
{


namespace detail
{


//
// helper to get return type of sum
//
template<class... Ts>
struct sum_type;

template<class T>
struct sum_type<T>:
   id<T>
{
};

template<class T, class U, class... Ps>
struct sum_type<T,U,Ps...>: 
   id<decltype(std::declval<T>() + std::declval<typename sum_type<U,Ps...>::type>())>
{
};


} // namespace detail

//
//
//
template<class T>
constexpr T Sum(T t)
{
   return t;
}

//
// 
//
template<class T, class... Ts>
constexpr auto Sum(T t, Ts... ts)
   -> decltype(std::declval<T>()+std::declval<typename detail::sum_type<Ts...>::type>())
{
   return t + Sum(std::forward<Ts>(ts)...);
}

//
// OLD SCHOOL WAY
//
// forward declaration
//
template<class T, T... Args>
struct sum;

//
// induction step
//
template<class T, T FirstArg, T... Args>
struct sum<T,FirstArg,Args...>
{
   static const T value = FirstArg + sum<T,Args...>::value;
};

//
// end step
//
template<class T>
struct sum<T>
{
   static const T value = 0;
};

} // namespace meta
} // namespace libmda

#endif // LIBMDA_META_SUM_H_INCLUDED
