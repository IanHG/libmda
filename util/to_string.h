#ifndef LIBMDA_UTIL_TO_STRING_H_INCLUDED
#define LIBMDA_UTIL_TO_STRING_H_INCLUDED

#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

/**
 *
 **/
namespace libmda 
{
namespace util 
{

/**
 * convert floating point number to string with precision
 **/ 
template<class T>
std::string to_string_with_precision(T a, int prec = std::numeric_limits<T>::digits10, bool showpos = false)
{
   // test that T is floating point
   static_assert( std::is_floating_point<T>::value
                , "midas::util::to_string_with_precision(): Should only be called with float."
                );
   
   // do the converion
   std::ostringstream str_stream;
   if(showpos) str_stream.setf(std::ios::showpos);
   str_stream << std::scientific << std::setprecision(prec)
              << a;
   return str_stream.str();
}

/**
 * to_string for floating point
 **/
inline std::string to_string(float a) { return to_string_with_precision(a); }
inline std::string to_string(double a) { return to_string_with_precision(a); }
inline std::string to_string(long double a) { return to_string_with_precision(a); }

/**
 * general to_string
 **/
template<class T>
inline std::string to_string(T a) { return std::to_string(a); }

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_TO_STRING_H_INCLUDED */
