#ifndef LIBMDA_TYPE_INFO_H_INCLUDED
#define LIBMDA_TYPE_INFO_H_INCLUDED

/**
* Disclaimer: Blatantly copied from here:   http://stackoverflow.com/a/4541470/2964487
**/


#include <string>
#include <typeinfo>

namespace libmda
{
namespace util
{

std::string demangle(const char* name);

template <class T>
std::string type_of(const T& t) 
{
   return demangle(typeid(t).name());
}

template<class T>
std::string type_of()
{
   return demangle(typeid(T).name());
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_TYPE_INFO_H_INCLUDED */
