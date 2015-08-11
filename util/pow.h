#ifndef LIBMDA_UTIL_POW_H_ICNLUDED
#define LIBMDA_UTIL_POW_H_ICNLUDED

namespace libmda
{
namespace util
{
namespace detail
{

template<size_t N>
struct pow_impl;

template<>
struct pow_impl<0>
{
   template<class T>
   static typename std::decay<T>::type apply(T&& t)
   {
      return T(1);
   }
};

template<>
struct pow_impl<1>
{
   template<class T>
   static typename std::decay<T>::type apply(T&& t)
   {
      return t;
   }
};

template<size_t N>
struct pow_impl
{
   template<class T>
   static typename std::decay<T>::type apply(T&& t)
   {
      return t*pow_impl<N-1>::apply(t);
   }
};

} /* namespace detail */

template<size_t N, class T>
typename std::decay<T>::type pow(T&& t)
{
   //return detail::pow_impl<N>::apply(std::forward<T>(t));
   return detail::pow_impl<N>::apply(t);
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_POW_H_ICNLUDED */
