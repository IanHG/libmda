#include "print_variadic.h"

namespace libmda
{
namespace util
{

//
// print variadic no arguments 
//
void print_variadic(std::ostream& stream, std::string delim)
{
   #ifdef PRINT_VARIADIC_WARNING
   print_warning(detail::WARNING_print_variadic_no_arguments());
   #endif /* PRINT_VARIADIC_WARNING */
}

} // namespace util
} // namespace libmda
