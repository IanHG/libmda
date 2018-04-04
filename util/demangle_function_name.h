#ifndef DEMANGLE_FUNCTION_NAME_H_INCLUDED
#define DEMANGLE_FUNCTION_NAME_H_INCLUDED

#ifdef __GNUC__
#include <cxxabi.h>
#endif

//#include "demangle_function.h"

namespace libmda
{
namespace util
{

char * demangle(const char *name, char *buffer, size_t buflen, int* status);

char* demangle_function_name(const char* mangled_name
                           , char* output_buffer
                           , size_t* length
                           , int* status
                           );

} /* namespace util */
} /* namespace libmda */

#endif /* DEMANGLE_FUNCTION_NAME_H_INCLUDED */
