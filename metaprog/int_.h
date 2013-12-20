#ifndef LIBMDA_METAPROG_INT_H
#define LIBMDA_METAPROG_INT_H

#include<iostream>
#include "iterator.h"

namespace libmda
{
namespace metaprog
{
namespace detail
{
   // no implementation details as of yet
} // namespace detail 

template<int N>
struct int_
{
   using tag = bidirectional_iterator_tag;
   
   typedef int_<N> type;
   typedef int     value_type;
   enum{ value = N };

   typedef int_<N+1> next;
   typedef int_<N-1> prev;
};

template<int N>
std::ostream& operator<<(std::ostream& a_stream, int_<N>)
{ a_stream << N; return a_stream; }

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_INT_H */
