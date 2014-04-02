#ifndef LIBMDA_NTH_TYPE_OF_H_INCLUDED
#define LIBMDA_NTH_TYPE_OF_H_INCLUDED

namespace libmda
{
namespace meta
{

// Declare primary template
template<int I, typename... Ts>
struct nth_type_of;

// Base step
template<typename T, typename... Ts>
struct nth_type_of<0, T, Ts...>
{
   using type = T;
};

// Induction step
template<int I, typename T, typename... Ts>
struct nth_type_of<I, T, Ts...>
{
   using type = typename nth_type_of<I - 1, Ts...>::type;
};

// interface
template<int I, typename... Ts>
using Nth_type_of = typename nth_type_of<I,Ts...>::type;

// Helper meta-function for retrieving the first type in a parameter pack
template<typename... Ts>
struct first_type_of
{
   using type = typename nth_type_of<0, Ts...>::type;
};

template<typename... Ts>
using First_type_of = typename first_type_of<Ts...>::type;

// Helper meta-function for retrieving the last type in a parameter pack
template<typename... Ts>
struct last_type_of
{
   using type = typename nth_type_of<sizeof...(Ts) - 1, Ts...>::type;
};

template<typename... Ts>
using Last_type_of = typename last_type_of<Ts...>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_NTH_TYPE_OF_H_INCLUDED */
