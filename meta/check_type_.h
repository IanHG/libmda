#ifndef LIBMDA_METAPROG_TYPECHECK_H
#define LIBMDA_METAPROG_TYPECHECK_H

#include "std_wrappers.h"

namespace libmda
{
namespace meta
{

// Ensure a parameter pack T consists entirely of types that are convertible to U
template<typename U, typename... T> 
struct check_type_;

template<typename U, typename T> 
struct check_type_<U,T>
{
    //static const bool value = std::is_same<U,T>::value; // to hard a condition
                                                          // will make some un-intuitive
                                                          // compilations errors
    ///static const bool value = std::is_convertible<U,T>::value;
    static const bool value = Convertible<U,T>();
};

template<typename U, typename Head, typename... Tail> 
struct check_type_<U, Head, Tail...>
{
    //static const bool value = (std::is_same<U,Head>::value  // same as above
    //   && check_type_<U,Tail...>::value);
    //static const bool value = (std::is_convertible<U,Head>::value  // same as above
    //   && check_type_<U,Tail...>::value);
    static const bool value = (Convertible<U,Head>() && check_type_<U,Tail...>::value);
};

template<int N, typename U, typename... T>
struct check_type_and_size_
{
   //static const bool value = (sizeof...(T) == N 
   //   && check_type_<U,T...>::value);
   static const bool value = (sizeof...(T) == N && All(Convertible<T,U>()...));
};

template<int N, typename U>
struct check_type_and_size_<N,U>
{
   static const bool value = (0 == N);
};

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_TYPECHECK_H */
