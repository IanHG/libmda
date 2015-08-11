#ifndef LIBMDA_UTIL_STATIC_VALUE_H_INCLUDED
#define LIBMDA_UTIL_STATIC_VALUE_H_INCLUDED

namespace libmda
{
namespace util
{

//
// static const
//
template<class T, T V>
struct static_value: std::integral_constant<T,V>
{
   static const T value = V;
   
   static_value(int = 0)
   {
   }
};

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_STATIC_VALUE_H_INCLUDED */
