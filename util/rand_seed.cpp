#include "rand_seed.h"

namespace libmda
{
namespace util
{

void seed()
{
   static detail::rand_seed rs;
}

} /* namespace imda */
} /* namespace libmda */
