#ifndef LIBMDA_METAPROG_TUPLE_H
#define LIBMDA_METAPROG_TUPLE_H

#include "../metaprog/if.h"

#include "iterator.h"
#include "permute.h"
#include "at.h"
#include "empty.h"
#include "push_back.h"
#include "push_front.h"
#include "pop_back.h"
#include "pop_front.h"
#include "range.h"
#include "catenate.h"
#include "insert.h"
#include "find.h"
#include "find_if.h"
#include "permute.h"
#include "partition.h"
#include "remove_if.h"
#include "remove.h"
#include "unique.h"
#include "make_type.h"

namespace libmda
{
namespace metaprog
{

/***********************/
// forward declarations
/***********************/
template<typename...> struct tuple;
struct tuple_tag { };
template<class...> struct permutation_;

namespace detail
{
/***********************/
// empty implementation for tuple
/***********************/
template<class T> struct empty_tuple_impl { using type = tuple<>; };
template<> struct empty_impl<tuple_tag>
{
   template<class T> struct apply: empty_tuple_impl<T> { }; 
};

/***********************/
// push_back implementation tuple
/***********************/
template<class    T, class... U> struct push_back_tuple_impl;
template<class... T, class... U> struct push_back_tuple_impl<tuple<T...>,U...>
{ using type = tuple<T...,U...>; };
template<> struct push_back_impl<tuple_tag>
{
   template<class T, class... U> struct apply: push_back_tuple_impl<T,U...> { }; 
};

/***********************/
// push_front implementation tuple
/***********************/
template<class    T, class... U> struct push_front_tuple_impl;
template<class... T, class... U> struct push_front_tuple_impl<tuple<T...>,U...>
{ using type = tuple<U...,T...>; };
template<> struct push_front_impl<tuple_tag>
{
   template<class T, class... U> struct apply: push_front_tuple_impl<T,U...> { }; 
};

/***********************/
// pop_back implementation tuple (NBNBNB! not implemted yet ! )
/***********************/ 
template<class T> struct pop_back_tuple_impl{ };
//{ static_assert(false, "this is not implemented"); };
//{ static_assert(!Is_same<T,empty<T> >(),"pop_back: tuple is empty :S"); };
//template<typename T, typename... U> struct pop_back_tuple_impl<tuple<U...,T> >
//{ using type = tuple<U...>; };
template<> struct pop_back_impl<tuple_tag>
{
   template<class T> struct apply: pop_back_tuple_impl<T> 
   { 
   
   }; 
};

/***********************/
// pop_front implementation tuple
/***********************/
template<class T> struct pop_front_tuple_impl
{ static_assert(!Is_same<T,empty<T> >(),"pop_front: tuple is empty :S"); };
template<typename T, typename... U> struct pop_front_tuple_impl<tuple<T,U...> >
{ using type = tuple<U...>; };
template<> struct pop_front_impl<tuple_tag>
{
   template<class T> struct apply: pop_front_tuple_impl<T> { }; 
};

/***********************/
// at implementation for tuple
/***********************/
template<class, size_t, size_t> struct at_tuple_impl2;
template<size_t N, size_t M, typename T, typename... U> 
struct at_tuple_impl2<tuple<T,U...>,N,M>: at_tuple_impl2<tuple<U...>,N+1,M> { };
template<size_t N, typename T, typename... U> 
struct at_tuple_impl2<tuple<T,U...>,N,N> { using type = T; };

// indirection to check for overcounting
template<class T, size_t N> struct at_tuple_impl: at_tuple_impl2<T,0,N> 
{ static_assert(N < T::Size(), "overcount"); };

template<> struct at_impl<tuple_tag>
{ 
   template<class T, int N> struct apply: at_tuple_impl<T,N> { };
};

/***********************/
// range implementation for tuple
/***********************/
template<class B, class E, class T> struct range_tuple_impl: 
   range_tuple_impl<next<B>, E, push_back<T,deref<B> > > { };
template<class E, class T> struct range_tuple_impl<E,E,T>
{ using type = T; };
template<> struct range_impl<tuple_tag>
{
   template<class T, size_t N, size_t M> struct apply: 
      range_tuple_impl<iterator<T,N>,iterator<T,M>, empty<T> > 
   { static_assert(N<=M,"range_impl: N>M :("); };
};

/***********************/
// catenate implementation for tuple
/***********************/
template<class T, class U>             struct catenate_tuple_impl;
template<typename... T, typename... U> struct catenate_tuple_impl<tuple<T...>,tuple<U...> >
{ using type = tuple<T...,U...>; };
template<> struct catenate_impl<tuple_tag>
{
   template<class T, class U> struct apply: catenate_tuple_impl<T,U> { };
};

/***********************/
// insert implementation for tuple
/***********************/
// insert implementation for tuple
// needs Range and Push_back
template<class T, typename U, size_t N> struct insert_tuple_impl
{
   using type = catenate<push_back<range<T,0,N>,U>,range<T,N,T::Size()> >;
};
template<> struct insert_impl<tuple_tag>
{
   template<class T, typename U, size_t N> struct apply: insert_tuple_impl<T,U,N> { };
};

/*************************/
// remove_if implementation
/*************************/
template<class B, class E, class Pred, class Res> 
struct remove_if_tuple_impl: If<!Pred::template apply<deref<B> >::value
                               , remove_if_tuple_impl<next<B>, E, Pred, push_back<Res,deref<B> > > // if Pred is false push back dererenced B
                               , remove_if_tuple_impl<next<B>, E, Pred, Res >                      // if Pred is true we do not push back
                             >
{ };
template<class E, class Pred, class Res>
struct remove_if_tuple_impl<E,E,Pred,Res>
{ using type = Res; };
template<> struct remove_if_impl<tuple_tag>
{
   template<class T, class Pred> struct apply: 
      remove_if_tuple_impl<begin<T>, end<T>, Pred, empty<T> > { };
};

/***********************/
// iterator implementation
/***********************/
template<class T, size_t N, size_t M> struct tuple_iterator_impl // general tuple iter
{
   using tag   = bidirectional_iterator_tag;
   using next  = iterator<T,N+1>;
   using prev  = iterator<T,N-1>;
   using deref = at<T,N>;
   using pos   = mpsize_t<N>;
};
template<class T, size_t M> struct tuple_iterator_impl<T,0,M>  // begin iter specialization
{
   using tag   = bidirectional_iterator_tag;
   using next  = iterator<T,1>;
   using prev  = iterator<T,T::Size()>; // for now prev will point to end<T>
   using deref = at<T,0>;
   using pos   = mpsize_t<0>;
};
template<class T, size_t N> struct tuple_iterator_impl<T,N,N>  // end iter specialization
{
   using tag   = bidirectional_iterator_tag;
   // make overflow iterator for when using next here !!
   using next  = iterator<T,0>; // for now next will point to start... (isnt this fine ?)
   using prev  = iterator<T,N-1>;
   using deref = void; // define deref for end as void
   using pos   = mpsize_t<N>;
};

template<> struct iterator_impl<tuple_tag>
{
   template<class T, int N> struct apply
   {
      static_assert(N>=0,        "iterator_impl for tuple: N<0..."); 
      static_assert(N<=T::Size(),"iterator_impl for tuple: N>T::Size()..."); 
      using type = tuple_iterator_impl<T,size_t(N),T::Size()>;
   };
};

// NB FIX to use tags!!!
// begin impl for tuple iterators
template<class T> struct begin_tuple_impl
{ using type = iterator<T,0>; };
template<> struct begin_impl<tuple_tag>
{ 
   template<class T> struct apply: begin_tuple_impl<T> { };
};
// end impl for tuple iterators
template<class T> struct end_tuple_impl
{ using type = iterator<T,T::Size()>; };
template<> struct end_impl<tuple_tag>
{
   template<class T> struct apply: end_tuple_impl<T> { };
};

/***********************/
// find_if implementation
/***********************/
template<class B, class E, class Pred> struct find_if_tuple_impl:
   If<Pred::template apply<deref<B> >::value
    , make_type<B>
    , find_if_tuple_impl<next<B>, E, Pred>
   >
{ };
template<class E, class Pred> struct find_if_tuple_impl<E,E,Pred>
{ using type = E; };

template<> struct find_if_impl<tuple_tag>
{
   template<class T, class Pred> struct apply: 
      find_if_tuple_impl<begin<T>, end<T>, Pred> { };
};

/***********************/
// permute implementation
/***********************/
template<class T, class    U> struct permute_tuple_impl;
template<class T, class... U> struct permute_tuple_impl<T, permutation_<U...> >
{
   using type = tuple<at<T,U::value>...>;
};
template<> struct permute_impl<tuple_tag>
{
   template<class T, class U> struct apply: permute_tuple_impl<T,U> { };
};

/***********************/
// partition
// B/E  : begin and end iterators
// Pred : must be a class that provides an internal apply class,
//        that takes a single template argument, and has an internal value
// True : gathers elements for which Pred::apply::value is true
// False: gathers elements for which Pred::apply::value is false
/***********************/
template<class B, class E, class Pred, class True, class False> 
struct partition_tuple_impl: If<Pred::template apply<deref<B> >::value
                         , partition_tuple_impl<next<B>, E, Pred, push_back<True,deref<B> >, False >
                         , partition_tuple_impl<next<B>, E, Pred, True, push_back<False,deref<B> > > 
                       >
{ };
template<class E, class Pred, class True, class False> 
struct partition_tuple_impl<E, E, Pred, True, False>
{
   using t = True;
   using f = False;
};

template<> struct partition_impl<tuple_tag>
{
   template<class T, class Pred> struct apply: 
      partition_tuple_impl<begin<T>, end<T>, Pred, empty<T>, empty<T> > { };
};

/***********************/
// all_unique for tuple
/***********************/
template<typename... T> struct all_unique<tuple<T...> >: all_unique<T...> { };
} // namespace detail

// tuple definition
template<typename... T> struct tuple
{
   using This = tuple<T...>;
   using tag  = tuple_tag;
   static const int size = sizeof...(T);

   static constexpr size_t Size()     { return size; };
   static constexpr bool   Is_empty() { return Size() == 0; };
   //template<typename U>
   //static constexpr size_t Find() { return detail::find<U,This>::value; }

   // 
   //using Empty = empty<This>;

   //// get type of argument N
   //template<size_t N>
   //using At = at<This,N>;
   //
   //// get types of argument N... as tuple object
   //template<size_t... N>
   //using Att = tuple<at<This,N>...>;
   //
   //// iterator interface
   ////template<size_t N> using Iterator = iterator<This,N>;
   //using Begin = begin<This>;
   //using End   = end  <This>;
   //
   //// get range
   //template<size_t N, size_t M>
   //using Range = range<This,N,M>;

   //// push back/front
   //template<typename... U>
   //using Push_back  = push_back <This,U...>;
   //template<typename... U>
   //using Push_front = push_front<This,U...>;

   //// insert T at N push rest of elements back one place
   //template<typename U, size_t N>
   //using Insert = insert<This,U,N>;

   //// permute
   //template<class U>
   //using Permute = permute<This,U>;
};

} // namespace metaprog
} // namespace libmda
#endif /* LIBMDA_METAPROG_TUPLE_H */
