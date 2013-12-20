#ifndef LIBMDA_ITERATOR_H
#define LIBMDA_ITERATOR_H

#include "../metaprog/std_wrappers.h"
#include "../metaprog/if.h"
#include "../basic_using.h"
#include "tag.h"

namespace libmda
{
namespace metaprog
{
/******************/
// iterator tags 
/******************/
struct forward_iterator_tag       { };
struct bidirectional_iterator_tag   { };
struct random_access_iterator_tag { };

namespace detail
{
   // nothing in here for iterator tags... YET !
} // namespace detail

template<class Iter>
constexpr bool Forward_iterator()
{ 
   using tag = Tag<Iter>;
   return (Is_same<tag,forward_iterator_tag>()       ||
           Is_same<tag,bidirectional_iterator_tag>() || 
           Is_same<tag,random_access_iterator_tag>() );
}

template<class Iter>
constexpr bool Backward_iterator()
{ 
   using tag = Tag<Iter>;
   return (Is_same<tag,bidirectional_iterator_tag>() || 
           Is_same<tag,random_access_iterator_tag>() );
}

template<class Iter>
constexpr bool Bidirectional_iterator()
{ 
   using tag = Tag<Iter>;
   return (Is_same<tag,bidirectional_iterator_tag>() || 
           Is_same<tag,random_access_iterator_tag>() );
}

template<class Iter>
constexpr bool Random_access_iterator()
{ 
   using tag = Tag<Iter>;
   return (Is_same<tag,random_access_iterator_tag>());
}  

/******************/
// iterator tags end
/******************/


/************************************/
// iterator interface
/************************************/

namespace detail
{
//template<int N, class T> struct iterator;
template<class> struct iterator_impl;
} // namespace detail
template<class T, int N> using  iterator = 
      typename detail::iterator_impl<Tag<T> >::template apply<T,N>::type;

/************************************/
// next / prev / deref for iterators
/************************************/
namespace detail
{
template<class T> struct next_impl
{
   static_assert(Forward_iterator<T>(),"not a forward iterator");
   using type = typename T::next;
};

template<class T> struct prev_impl
{
   static_assert(Backward_iterator<T>(),"not a backward iterator");
   using type = typename T::prev;
};

template<class T> struct pos_impl
{
   using type = typename T::pos;
};

} // namespace detail

// interface next / prev / deref
template<class T>
using next  = Type<detail::next_impl<T> >;
template<class T>
using prev  = Type<detail::prev_impl<T> >;
template<class T>
using pos   = Type<detail::pos_impl<T>  >;
template<class T>
using deref = typename T::deref;
/************************************/
// next / prev / deref for iterators END
/************************************/

/************************************/
// advance
/************************************/

namespace detail {
// advance
template<class T, int N> struct advance_;
template<class T, int N> struct advance_incr:
   advance_<next<T>,N-1> { };
template<class T, int N> struct advance_decr:
   advance_<prev<T>,N+1> { };
template<class T, int N> struct advance_:
   If<(N>0),advance_incr<T,N>,advance_decr<T,N> > { };
template<class T> struct advance_<T,0>
{ using type = T; };

} // namespace detail
// advance interface
template<class T, int N>
using advance = Type<detail::advance_<T,N> >;


/************************************/
// begin / end
/************************************/

namespace detail
{
// begin / end
template<class T> struct begin_impl;
template<class T> struct end_impl;
} // namespace detail
// begin / end interface
template<class T> using begin 
   = typename detail::begin_impl<Tag<T> >::template apply<T>::type;
template<class T> using end   
   = typename detail::end_impl  <Tag<T> >::template apply<T>::type;

} // namespace metaprog

// interface for iterator
// maybe remove from here... but then again its convinient :)
using metaprog::next;
using metaprog::prev;
using metaprog::deref;
using metaprog::advance;
using metaprog::begin;
using metaprog::end;

} // namespace libmda
#endif /* LIBMDA_ITERATOR_H */
