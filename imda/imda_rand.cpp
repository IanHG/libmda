#include "imda_rand.h"

namespace libmda
{
namespace imda
{
namespace detail
{

void seed()
{
   static rand_seed rs;
}

} /* namespace detail */
} /* namespace imda */
} /* namespace libmda */
