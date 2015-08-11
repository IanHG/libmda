#ifndef LIBMDA_OUTPUT_CALL_ADDR_H_INCLUDED
#define LIBMDA_OUTPUT_CALL_ADDR_H_INCLUDED

#include <iostream>
#include <unistd.h>
#include <string.h>

namespace libmda
{
namespace util
{

namespace detail
{

template<unsigned I>
struct plus_one_impl
{
   static constexpr unsigned value = I + 1;
};

} /* namespace detail */


template<unsigned I>
constexpr unsigned plus_one()
{
   return detail::plus_one_impl<I>::value;
}

// get path to executed binary
bool get_self_path(char buffer[], size_t size, ssize_t& len);

// get file+line from function address if we have compiled with debug flag
bool address_to_line(void* call_addr, char* buffer, size_t size_of_buffer);

std::string wrap_address_to_line(void* call_addr);

template<unsigned I>
inline std::string return_address()
{
   return wrap_address_to_line(__builtin_return_address(I+1));
}

void output_call_addr(std::ostream& os, void* call_addr, char tab='\0');

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_OUTPUT_CALL_ADDR_H_INCLUDED */
