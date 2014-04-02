/**
* Disclaimer: Blatantly copied from here:   http://stackoverflow.com/a/4541470/2964487
**/


#include "type_info.h"
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
namespace libmda
{
namespace util
{

std::string demangle(const char* name) 
{
   int status = -4; // some arbitrary value to eliminate the compiler warning

   // enable c++11 by passing the flag -std=c++11 to g++
   std::unique_ptr<char, void(*)(void*)> res {
      abi::__cxa_demangle(name, NULL, NULL, &status),
      std::free
   };

   return (status==0) ? res.get() : name ;
}
} /* namespace util */
} /* namespace libmda */

#else

namespace libmda
{
namespace util
{
// does nothing if not g++
std::string demangle(const char* name) 
{
   return name;
}
} /* namespace util */
} /* namespace libmda */

#endif /* __GNUG__ */

//#include "type.h"
//#ifdef __GNUG__
//#include <cstdlib>
//#include <memory>
//#include <cxxabi.h>
//
//   struct handle {
//          char* p;
//              handle(char* ptr) : p(ptr) { }
//                  ~handle() { std::free(p); }
//   };
//
//   std::string demangle(const char* name) {
//
//          int status = -4; // some arbitrary value to eliminate the compiler warning
//
//              handle result( abi::__cxa_demangle(name, NULL, NULL, &status) );
//
//                  return (status==0) ? result.p : name ;
//   }
//
//#else
//
//   // does nothing if not g++
//   std::string demangle(const char* name) {
//          return name;
//   }
//
//#endif /* __GNUG__ */

