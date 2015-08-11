#ifndef LIBMDA_UTIL_STATIC_TYPE_H_INCLUDED
#define LIBMDA_UTIL_STATIC_TYPE_H_INCLUDED

namespace libmda
{
namespace util
{

//
// static const
//
template<class T>
struct static_type
{
   //static const T value = V;
   
   static_type(int = 0)
   {
   }
};

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_STATIC_TYPE_H_INCLUDED */
