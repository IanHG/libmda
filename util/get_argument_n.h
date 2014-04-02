#ifndef GET_ARGUMENT_N_H
#define GET_ARGUMENT_N_H

#include "../meta/nth_type_of.h"

namespace libmda
{
namespace util
{

template<int N> 
struct get_argument_n
{
   template<typename U, typename... T> 
   static meta::Nth_type_of<N,U,T...>& 
   get(U& arg1, T&... arg)
   {
      return get_argument_n<N-1>::get(arg...);
   }
};

template<> 
struct get_argument_n<0>
{
   template<typename U, typename... T> 
   static U& get(U& arg1, T&... arg)
   {
      return arg1;
   }
};

} // namespace util
} // namespace libmda

#endif /* GET_ARGUMENT_N_H */
