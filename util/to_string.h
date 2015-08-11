#include <string>
#include <sstream>
#include <iomanip>

/**
 *
 **/
namespace libmda {
namespace util {

/**
 * convert floating point number to string with precision
 **/ 
template<class T>
std::string to_string_with_precision(T a, int prec = std::numeric_limits<T>::digits10)
{
   // test that T is floating point
   static_assert(std::is_floating_point<T>::value
               , "midas::util::to_string_with_precision(): Should only be called with floating point type."
               );
   
   // do the conversion
   std::ostringstream str_stream;
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
