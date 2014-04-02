#ifndef LIBMDA_PRINT_VARIADIC_H_INCLUDED
#define LIBMDA_PRINT_VARIADIC_H_INCLUDED

#include<iostream>
#include<string>
#include"enforce.h"
#include"warning.h"

// comment in to get compiler warning when printing no arguments
//#define PRINT_VARIADIC_WARNING

namespace libmda
{
namespace util
{

namespace detail
{

//
struct WARNING_print_variadic_no_arguments
{
};

} // namespace detail

//
// print variadic no arguments 
//
void print_variadic(std::ostream& stream, std::string delim);

//
//  print variadic end step/one argument
//
template<class T>
void print_variadic(std::ostream& stream, std::string delim, T&& t)
{
   stream << t;
}

//
// print variadic recursively
//
template<class T, class... Ts>
void print_variadic(std::ostream& stream, std::string delim, T&& t, Ts&&... ts)
{
   stream << t << delim;
   print_variadic(stream,delim,std::forward<Ts>(ts)...);
}

} // namespace util
} // namespace libmda

#endif /* LIBMDA_PRINT_VARIADIC_H_INCLUDED */
