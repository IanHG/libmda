#ifndef LIBMDA_META_PRINT_META_TUPlE_H_INCLUDED
#define LIBMDA_META_PRINT_META_TUPLE_H_INCLUDED

#include<iostream>
#include<string>

namespace libmda
{
namespace meta
{

namespace detail
{

template<class B, class E>
struct print_meta_tuple_impl
{
   void operator()(std::ostream& stream, std::string delim)
   {
      deref<B> b;
      stream << b << delim;
      print_meta_tuple_impl<next<B>,E>()(stream,delim);
   }
};

template<class E>
struct print_meta_tuple_impl<E,E>
{
   void operator()(std::ostream& stream, std::string delim)
   {
   }
};

} // namespace detail

//
// print variadic recursively
//
template<class T>
void print_meta_tuple(std::ostream& stream, std::string delim)
{
   detail::print_meta_tuple_impl<begin<T>, end<T> >()(stream,delim);
}

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_META_PRINT_META_TUPLE_H_INCLUDED */
