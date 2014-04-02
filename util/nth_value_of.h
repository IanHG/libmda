#ifndef LIBMDA_NTH_VALUE_OF_H_INCLUDED
#define LIBMDA_NTH_VALUE_OF_H_INCLUDED

#include "../meta/std_wrappers.h"
#include "../meta/nth_type_of.h"

namespace libmda
{
namespace util
{

// Base step
template<int I, typename T, typename... Ts>
auto nth_value_of(T&& t, Ts&&... args) ->
    meta::Enable_if<(I == 0), decltype(std::forward<T>(t))>
{
   return std::forward<T>(t);
}

// Induction step
template<int I, typename T, typename... Ts>
auto nth_value_of(T&& t, Ts&&... args) ->
    meta::Enable_if<(I > 0), decltype(
                  std::forward<meta::Nth_type_of<I, T, Ts...> >(
                                 std::declval<meta::Nth_type_of<I, T, Ts...> >()
                  )
             )>
{
   using return_type = meta::Nth_type_of<I, T, Ts...>;
   return std::forward<return_type>(nth_value_of<I - 1>((std::forward<Ts>(args))...));
}

// Helper function for retrieving the first value of an argument pack
template<typename... Ts>
auto first_value_of(Ts&&... args) ->
    decltype(std::forward<meta::First_type_of<Ts...> >(
               std::declval<meta::First_type_of<Ts...> >()
               )
            )
{
   using return_type = meta::First_type_of<Ts...>;
   return std::forward<return_type>(nth_value_of<0>((std::forward<Ts>(args))...));
}

// Helper function for retrieving the last value of an argument pack
template<typename... Ts>
auto last_value_of(Ts&&... args) ->
    decltype(std::forward<meta::Last_type_of<Ts...> >(
                std::declval<meta::Last_type_of<Ts...> >()
                )
            )
{
   using return_type = meta::Last_type_of<Ts...>;
   return std::forward<return_type>(nth_value_of<sizeof...(Ts) - 1>((std::forward<Ts>(args))...));
}

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_NTH_VALUE_OF_H_INCLUDED */
