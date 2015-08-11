#ifndef LIBMDA_UTIL_RAND_SEED_H_INCLUDED
#define LIBMDA_UTIL_RAND_SEED_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <type_traits>

#include "../meta/std_wrappers.h"

namespace libmda
{
namespace util
{
namespace detail
{

struct rand_seed
{
   rand_seed()
   {
      srand(time(NULL));
      //srand(400);
   }
};

} /* namespace detail */

void seed();

template<class T
       , iEnable_if<std::is_floating_point<T>::value> = 0
       >
T rand_float()
{
   seed();
   return (T)rand() / RAND_MAX;
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_RAND_SEED_H_INCLUDED */
