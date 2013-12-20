#ifndef LIBMDA_METAPROG_UNIQUE_H
#define LIBMDA_METAPROG_UNIQUE_H

namespace libmda
{
namespace metaprog
{
namespace detail
{

// is first element in a set of types unique?
template<typename...> struct unique; 
template<typename T, typename U, typename... V> struct unique<T,U,V...>
{ static const bool value = unique<T,V...>::value; };
template<typename T, typename... V> struct unique<T,T,V...>
{ static const bool value = false; };
template<typename T> struct unique<T>
{ static const bool value = true; };

// are all elements in a set of types unique?
template<typename...> struct all_unique;
template<typename T, typename... U> struct all_unique<T,U...>
{ static const bool value = unique<T,U...>::value && all_unique<U...>::value; };
template<> struct all_unique<>
{ static const bool value = true; };

// is element unique in a set of size_t
template<size_t...> struct i_unique;
template<size_t M, size_t P, size_t... O>
struct i_unique<M,P,O...>
{ static const bool value = (M!=P && i_unique<M,O...>::value); };
template<size_t M>
struct i_unique<M>
{ static const bool value = true; };

} // namespace detail

// interface for all_unique
template<typename... T>
constexpr bool All_unique()
{ return detail::all_unique<T...>::value; }

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_UNIQUE_H */
