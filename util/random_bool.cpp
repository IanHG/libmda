#include "random_bool.h"

#include <stdlib.h>

#include "rand_seed.h"

namespace libmda
{
namespace util
{

bool random_bool()
{
   seed();
   return rand() % 2 == 1;
}

} /* namespace util */
} /* namespace libmda */
