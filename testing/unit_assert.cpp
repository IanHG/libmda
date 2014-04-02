#include "unit_assert.h"

namespace libmda
{
namespace testing
{

detail::file_info make_file_info(const char* file, const unsigned int line)
{
   return detail::file_info(file, line);
}

} /* namespace libmda */
} /* namespace testing */
