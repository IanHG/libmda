#ifndef LIBMDA_INDEX_H_INCLUDED
#define LIBMDA_INDEX_H_INCLUDED

// std header
#include<iostream>

// libmda headers
#include "id.h"
#include "if.h"
#include "catenate.h"
#include "empty.h"
#include "size.h"
#include "../util/print_variadic.h"

// Disclamer:
//    Inspired by Andy Prowls great answer to this question on Stack Overflow with few modifications plus some additions
//    http://stackoverflow.com/questions/14261183/how-to-make-generic-computations-over-heterogeneous-argument-packs-of-a-variadic
//

namespace libmda
{
namespace meta
{

//===============================================================================
// META-FUNCTIONS FOR CREATING AND MANIPULATING INDEX LISTS

//
//
//
struct index_list_tag
{
};

//
// The structure that encapsulates index lists
//
template <unsigned... Is>
struct index_list
{
   using tag = index_list_tag;
};

namespace detail
{
//
// catenate implementation for index_list
//
template<class T, class U>
struct catenate_index_list_impl;

template<unsigned... Is1, unsigned... Is2>
struct catenate_index_list_impl<index_list<Is1...>,index_list<Is2...> >:
   id<index_list<Is1...,Is2...> >
{
};

template<>
struct catenate_impl<index_list_tag>
{
   template<class T, class U> struct apply: catenate_index_list_impl<T,U>
   {
   };
};

//
// empty index_list
//
template<class T>
struct empty_index_list_impl:
   id<index_list<> >
{
};

template<>
struct empty_impl<index_list_tag>
{
   template<class T> struct apply: empty_index_list_impl<T>
   {
   };
};

//
// size imple
//
template<class T> 
struct size_index_list_impl;

template<unsigned... Is>
struct size_index_list_impl<index_list<Is...> >:
   id<size_cont<sizeof...(Is)> >
{
};

template<>
struct size_impl<index_list_tag>
{
   template<class T> struct apply: size_index_list_impl<T>
   {
   };
};


//
// Collects internal details for generating index ranges [MIN, MAX)
//
// Induction step
template <unsigned MIN, unsigned N, unsigned... Is>
struct range_builder : public range_builder<MIN, N - 1, N - 1, Is...>
{ 
};

// Base step
template <unsigned MIN, unsigned... Is>
struct range_builder<MIN, MIN, Is...>
{
   using type = index_list<Is...>;
};


//
// generate index list for types which satisfies a predicate "Pred"
//
// 
template<unsigned I, class Pred, class Index, typename... Ts>
struct index_list_if_builder_;

// induction step
template<unsigned I, class Pred, unsigned... Is, typename T, typename... Ts>
struct index_list_if_builder_<I,Pred,index_list<Is...>,T,Ts...>:
   If<Pred::template apply<T>::value
    , index_list_if_builder_<I+1,Pred,index_list<Is...,I>,Ts...>
    , index_list_if_builder_<I+1,Pred,index_list<Is...>  ,Ts...> 
    >
{ 
};

// base step
template<unsigned I, class Pred, class Index>
struct index_list_if_builder_<I,Pred,Index>
{
   using type = Index;
};

// wrapper
template<class Pred, typename... Ts>
struct index_list_if_builder: 
   index_list_if_builder_<0,Pred,index_list<>,Ts...>
{
};

} // namespace detail

//
// Meta-function that returns a [MIN, MAX) index range
//
template<unsigned MIN, unsigned MAX>
using index_range = typename detail::range_builder<MIN, MAX>::type;

//
//
//
template<class Pred, typename... Ts>
using index_list_if 
   = typename detail::index_list_if_builder<Pred,Ts...>::type;

//
//
//
template<unsigned... Is>
std::ostream& operator<<(std::ostream& a_stream, const index_list<Is...>)
{ 
   a_stream << "index_list: (";
   util::print_variadic(a_stream,",",Is...);
   a_stream << ")";
   return a_stream; 
}

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_INDEX_H_INCLUDED */
