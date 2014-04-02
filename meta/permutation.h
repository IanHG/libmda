#ifndef LIBMDA_PERMUTATION_H
#define LIBMDA_PERMUTATION_H

#include "mpsize_t.h"
#include "../meta/nth_type_of.h"
#include "iterator.h"
#include "tuple.h"
#include "permute.h"
#include "unique.h"

namespace libmda
{
namespace meta
{
/**************************/
// forward declaration
/**************************/
template<class... N> struct permutation_impl;
struct permutation_tag { };

namespace detail
{
//
// size
//
template<class T> 
struct size_permutation_impl;

template<template<class...> class Tuple, class... Ts> 
struct size_permutation_impl<Tuple<Ts...> >:
   id<size_cont<sizeof...(Ts)> >
{
};

template<> 
struct size_impl<permutation_tag>
{
   template<class T> struct apply : size_permutation_impl<T>
   {
   };
};

//
//
//
template<> 
struct at_impl<permutation_tag>
{ 
   template<class T, int N> 
   struct apply: at_tuple_impl<T,N> 
   { 
   };
};

/**************************/
// is this a valid permutation
/**************************/
template<size_t N, size_t M, size_t... O>
struct permutation_is_valid
{
   static const bool value = M<N &&  // M must be less than total number of elems
                             i_unique<size_t,M,O...>::value &&  // M must be unique
                             permutation_is_valid<N,O...>::value; // need to validate rest of elems
};
template<size_t N, size_t M>
struct permutation_is_valid<N,M>
{ 
   static const bool value = M<N && i_unique<size_t,M>::value; 
};

/**************************/
// permutation iterator
/**************************/
template<> struct iterator_impl<permutation_tag>
{ 
   template<class T, int N> struct apply
   {
      using type = tuple_iterator_impl<T,N,T::order >;
   };
};

/**************************/
// permute permutation by other permutation
/**************************/
template<class    T, class    U> 
struct permute_permutation_impl;

template<class... T, class... U> 
struct permute_permutation_impl<permutation_impl<T...>, permutation_impl<U...> >
{
   using type = permutation_impl<mpsize_t<permutation_impl<T...>::template index<U::value>()>...>;
};

template<> struct permute_impl<permutation_tag>
{
   template<class T, class U> 
   struct apply : permute_permutation_impl<T,U> 
   { 
   };
};

//*
// begin / end
//*
template<class T> struct begin_permutation_impl:
   id<iterator<T,0> >
{ 
};

template<> struct begin_impl<permutation_tag>
{ 
   template<class T> struct apply: begin_permutation_impl<T> 
   { 
   };
};

template<class T> struct end_permutation_impl:
   id<iterator<T,size<T>::value> >
{ 
};

template<> struct end_impl<permutation_tag>
{
   template<class T> struct apply: end_permutation_impl<T> 
   { 
   };
};

} // namespace detail

template<class... N>
class permutation_impl
{
   public:
      using tag  = permutation_tag;
      using This = permutation_impl<N...>;
      static const int order = sizeof...(N);

      template<size_t M>
      static constexpr size_t index() { return Nth_type_of<M,N...>::value; }
      template<size_t M>
      using At = Nth_type_of<M,N...>;
      
      template<size_t... M>
      using Permute = permute<This,permutation_impl<mpsize_t<M>...> >;

   private:
      // assert if it a valid permutation
      static const bool valid = detail::permutation_is_valid<order,N::value...>::value;
      static_assert(valid, "permutation not valid");
};

// interface !
template<size_t... N> using permutation = permutation_impl< mpsize_t<N> ...>;

} // namespace util
} // namespace libmda

#endif /* LIBMDA_PERMUTATION_H */
