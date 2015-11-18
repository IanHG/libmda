#ifndef LIBMDA_UTIL_COPY_UNIQUE_PTR_H_INCLUDED
#define LIBMDA_UTIL_COPY_UNIQUE_PTR_H_INCLUDED

#include <memory>
#include <type_traits>

#include "../meta/std_wrappers.h"

namespace libmda
{
namespace util
{
namespace detail
{

template<class T> struct is_array : std::false_type {};
template<class T> struct is_array<T[]> : std::true_type {};
 
}

/**
 *
 **/
template< class T
        , iEnable_if<!detail::is_array<T>::value> = 0
        >
std::unique_ptr<T> copy_unique_ptr(const std::unique_ptr<T>& ptr)
{
   return std::unique_ptr<T>(new T(*ptr));
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_COPY_UNIQUE_PTR_H_INCLUDED */
