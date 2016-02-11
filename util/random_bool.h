#ifndef LIBMDA_UTIL_RANDOM_BOOL_H_INCLUDED
#define LIBMDA_UTIL_RANDOM_BOOL_H_INCLUDED

#include "rand_seed.h"

namespace libmda
{
namespace util
{

/**
 *
 **/
bool random_bool();

/**
 *
 **/
template<class T
       , iEnable_if<std::is_floating_point<T>::value> = 0 
       >
T random_sign()
{
   return rand_float<T>() >= 0.5 ? T(1.0) : T(-1.0);
}

} /* namespace util */
} /* namespace libmda */


#endif /* LIBMDA_UTIL_RANDOM_BOOL_H_INCLUDED */
