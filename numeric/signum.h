#ifndef LIBMDA_UTIL_SIGNUM_H_INCLUDED
#define LIBMDA_UTIL_SIGNUM_H_INCLUDED

//
// Disclaimer: taken from Stack Overflow http://stackoverflow.com/a/4609795/2964487
//             all credit goes to user79758
//
//

#include <type_traits>

namespace libmda
{
namespace numeric
{

template <typename T> 
inline constexpr int signum(T x, std::false_type is_signed) 
{
   return T(0) < x;
}

template <typename T> 
inline constexpr int signum(T x, std::true_type is_signed) 
{
   return (T(0) < x) - (x < T(0));
}

template <typename T> 
inline constexpr int signum(T x) 
{
   return signum(x, std::is_signed<T>());
}

} /* namespace numeric */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_SIGNUM_H_INCLUDED */
