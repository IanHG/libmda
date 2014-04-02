#ifndef LIBMDA_METAPROG_UNIQUE_H
#define LIBMDA_METAPROG_UNIQUE_H

#include "val.h"

namespace libmda
{
namespace meta
{
namespace detail
{

//
// is first element in a set of types unique?
//
template<typename...> 
struct unique; 

template<typename T, typename U, typename... V> 
struct unique<T,U,V...>
{ 
   static const bool value = unique<T,V...>::value; 
};

template<typename T, typename... V> 
struct unique<T,T,V...>
{ 
   static const bool value = false; 
};

template<typename T> 
struct unique<T>
{ 
   static const bool value = true; 
};

//
// are all elements in a set of types unique?
//
template<typename...> 
struct all_unique;

template<typename T, typename... U> 
struct all_unique<T,U...>
{ 
   static const bool value = unique<T,U...>::value && all_unique<U...>::value; 
};

template<> 
struct all_unique<>:
   val<bool,true>
{ 
};

//
// is element unique in a set of specific types
//
template<typename T, T...> 
struct i_unique;

template<typename T, T M>
struct i_unique<T,M>
{ 
   static const bool value = true; 
};

template<typename T, T M, T P, T... O>
struct i_unique<T,M,P,O...>
{ 
   static const bool value = (M!=P && i_unique<T,M,O...>::value); 
};

//
// are all elements unique in set of size_t
//
template<typename T, T...>
struct i_all_unique;

template<typename T>
struct i_all_unique<T>
{
   static const bool value = true;
};

template<typename T, T I, T... Is>
struct i_all_unique<T,I,Is...>
{
   static const bool value = i_unique<T,I,Is...>::value && i_all_unique<T,Is...>::value;
};

} // namespace detail

//
// interface unique
//
template<class... Ts>
constexpr bool Unique()
{
   return detail::unique<Ts...>::value;
}

//
// interface for all_unique
//
template<class... Ts>
constexpr bool All_unique()
{ 
   return detail::all_unique<Ts...>::value; 
}

//
// interface for i_all_unique
// 
template<typename T, T... Is>
constexpr bool iAll_unique()
{
   return detail::i_all_unique<T,Is...>::value;
}

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_UNIQUE_H */
