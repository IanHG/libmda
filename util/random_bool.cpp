#include "random_bool.h"

#include <stdlib.h>

#include "rand_seed.h"

namespace libmda
{
namespace util
{

bool random_bool()
{
   return rand_int<int>() % 2 == 1;
}

} /* namespace util */
} /* namespace libmda */
