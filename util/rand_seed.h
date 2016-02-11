#ifndef LIBMDA_UTIL_RAND_SEED_H_INCLUDED
#define LIBMDA_UTIL_RAND_SEED_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <type_traits>
#include <random>

#include "../meta/std_wrappers.h"

namespace libmda
{
namespace util
{
namespace detail
{

/*! Seed and return a mersienne twister RNG.
 *
 */
inline std::mt19937& get_mersienne()
{
   static std::random_device r;
   static std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
   static std::mt19937 mersienne(seed);
   return mersienne;
}

} /* namespace detail */

/*! Get pseudo-random integer value
 *
 */
template< class T
        , iEnable_if<std::is_integral<T>::value> = 0
        >
T rand_int()
{
   auto& mersienne = detail::get_mersienne();
   return static_cast<T>(mersienne());
}

/*! Get pseudo-random floating point value between 0.0 and 1.0 
 *
 */
template< class T
        , iEnable_if<std::is_floating_point<T>::value> = 0
        >
T rand_float()
{
   auto& mersienne = detail::get_mersienne();
   return static_cast<T>(mersienne())/static_cast<T>(mersienne.max());
}

/*! Get pseudo-random floating point value between -1.0 and 1.0 
 *  *
 *   */
template< class T
        , iEnable_if<std::is_floating_point<T>::value> = 0
        >
T rand_signed_float()
{
   auto& mersienne = detail::get_mersienne();
   return static_cast<T>(2*mersienne())/static_cast<T>(mersienne.max()) - 1.0;
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_RAND_SEED_H_INCLUDED */
