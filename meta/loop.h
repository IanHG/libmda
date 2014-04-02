#ifndef LIBMDA_METAPROG_LOOP_H
#define LIBMDA_METAPROG_LOOP_H

#include "int_.h"
#include "iterator.h"

namespace libmda
{
namespace meta
{
/**************************/
// forward declarations
/**************************/
template<class N, class M> struct loop2_;
struct loop_tag { };

namespace detail
{
/**************************/
// loop iterator implementation
/**************************/
template<class I, class N, class M> struct loop_iterator_impl
{
   using tag   = bidirectional_iterator_tag;
   using prev  = loop_iterator_impl<libmda::meta::prev<I>, N, M>;
   using next  = loop_iterator_impl<libmda::meta::next<I>, N, M>;
   using deref = I;
};
template<class N, class M> struct loop_iterator_impl<N,N,M>
{
   using tag   = bidirectional_iterator_tag;
   using next  = loop_iterator_impl<libmda::meta::next<N>, N, M>;
   using deref = N;
};
template<class N, class M> struct loop_iterator_impl<M,N,M>
{
   using tag   = bidirectional_iterator_tag;
   using prev  = loop_iterator_impl<libmda::meta::prev<M>, N, M>;
   using deref = void;
};

template<> struct iterator_impl<loop_tag>
{
   template<class T, int I> struct apply
   {
      using type = advance<loop_iterator_impl<typename T::first, typename T::first, typename T::last>,I>;
   };
};

// begin impl for loop iterator
template<class T> struct begin_loop_impl
{ using type = iterator<T,0>; };
template<> struct begin_impl<loop_tag>
{
   template<class T> struct apply: begin_loop_impl<T> { };
};
// end impl for loop iterator
template<class T> struct end_loop_impl
{ using type = iterator<T,T::length>; };
template<> struct end_impl<loop_tag>
{
   template<class T> struct apply: end_loop_impl<T> { };
};
} // namespace detail


template<class N, class M>
struct loop2_
{
   using tag  = loop_tag;
   using This = loop2_<N,M>;
   
   using first = N;
   using last  = M;

   static const int length = M::value - N::value;
   //struct end { };
   //using Begin = begin<This>;
   //using End   = end  <This>;
};

template<int N, int M>
using loop = loop2_<int_<N>,int_<M> >;

} // namespace meta

// interface
//using meta::loop;

} // namespace libmda 
#endif /* LIBMDA_METAPROG_LOOP_H */
