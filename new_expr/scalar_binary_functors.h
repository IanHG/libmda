#ifndef LIBMDA_SCALAR_BINARY_FUNCTORS_H_INCLUDED
#define LIBMDA_SCALAR_BINARY_FUNCTORS_H_INCLUDED

#include<utility>

namespace libmda
{
namespace expr
{

template<class T1, class T2>
struct scalar_binary_functor
{
};

template<class T1, class T2>
struct scalar_plus: scalar_binary_functor<T1,T2>
{
   using result_type = decltype(std::declval<T1>() + std::declval<T2>());

   result_type operator()(const T1& t1, const T2& t2) const
   {
      return t1 + t2;
   }
};

} /* namespace libmda */
} /* namespace libmda */

#endif /* LIBMDA_SCALAR_BINARY_FUNCTORS_H_INCLUDED */
