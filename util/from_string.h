#ifndef LIBMDA_UTIL_FROM_STRING_H_INCLUDED_
#define LIBMDA_UTIL_FROM_STRING_H_INCLUDED_

#include <stdexcept>
#include "type_info.h"

namespace libmda
{
namespace util
{
namespace detail
{

template<class T> struct from_string_impl;

////////////////////////
//
// integer conversions
//
///////////////////////
//
// int
//
template<>
struct from_string_impl<int> {
   static int apply(const std::string& str, size_t* pend) {
      return std::stoi(str,pend);
   }
};
//
// long
//
template<>
struct from_string_impl<long> {
   static long apply(const std::string& str, size_t* pend) {
      return std::stol(str,pend);
   }
};
//
// long long
//
template<>
struct from_string_impl<long long> {
   static long long apply(const std::string& str, size_t* pend) {
      return std::stoll(str,pend);
   }
};

//////////////////////
//
// unsigned integer conversions
//
///////////////////////
//
// unsigned
// there is not stou, so we use stoul and check for out_of_range
template<>
struct from_string_impl<unsigned> {
   static unsigned apply(const std::string& str, size_t* pend) {
      unsigned long result = std::stoul(str,pend);
      if(result > std::numeric_limits<unsigned>::max()) throw std::out_of_range("stou");
      return result;
   }
};
//
// unsigned long
//
template<>
struct from_string_impl<unsigned long> {
   static unsigned long apply(const std::string& str, size_t* pend) {
      return std::stoul(str,pend);
   }
};
//
// unsigned long long
//
template<>
struct from_string_impl<unsigned long long> {
   static unsigned long long apply(const std::string& str, size_t* pend) {
      return std::stoull(str,pend);
   }
};


//////////////////////
//
// floating point conversions
//
///////////////////////
//
// float
//
template<>
struct from_string_impl<float> {
   static float apply(const std::string& str, size_t* pend) {
      return std::stof(str,pend);
   }
};
//
// double
//
template<>
struct from_string_impl<double> {
   static double apply(const std::string& str, size_t* pend) {
      return std::stod(str,pend);
   }
};
//
// long double
//
template<>
struct from_string_impl<long double> {
   static long double apply(const std::string& str, size_t* pend) {
      return std::stold(str,pend);
   }
};


} /* namespace detail */

/////////////////////////
//
// helper function
//
/////////////////////////
template<class T>
//inline T from_string(const std::string& str, size_t* pend) 
T from_string(const std::string& str, size_t* pend) 
{
   try
   {
      T result = detail::from_string_impl<T>::apply(str,pend);
      if(pend && *pend != str.size())
      {
         std::cout << " did not read complete string '" << str << "', when converting to '" 
                   << util::typeof(T()) << "'" << std::endl;
      }
      return result;
   }
   catch(std::exception& e) // catch std exceptions
   {
      std::cout << " from_string: caught std exception: " << e.what() << std::endl;
      exit(0);
   }
   catch(...) // catch everything else
   {
      std::cout << " from string: caught something " << std::endl;
      exit(0);
   }
} 

//////////////////////////
//
// from_string interface
//
//////////////////////////
template<class T>
inline T from_string(const std::string& str)
{
   size_t end;
   return from_string<T>(str,&end);
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_FROM_STRING_H_INCLUDED_ */
