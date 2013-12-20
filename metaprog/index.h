#ifndef LIBMDA_INDEX_H_INCLUDED
#define LIBMDA_INDEX_H_INCLUDED

#include "if.h"

// Disclamer:
//    Heavily inspired by Andy Prowls answer to this question on Stack Overflow with few modifications/additions
//    http://stackoverflow.com/questions/14261183/how-to-make-generic-computations-over-heterogeneous-argument-packs-of-a-variadic
//

namespace libmda
{
namespace metaprog
{

//===============================================================================
// META-FUNCTIONS FOR CREATING INDEX LISTS

// The structure that encapsulates index lists
template <unsigned... Is>
struct index_list
{
};

// Collects internal details for generating index ranges [MIN, MAX)
namespace detail
{
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

} // namespace detail

// Meta-function that returns a [MIN, MAX) index range
template<unsigned MIN, unsigned MAX>
using index_range = typename detail::range_builder<MIN, MAX>::type;

// generate index list for types which satisfies a predicate "Pred"
namespace detail
{
   // 
   template<int I, class Pred, class Index, typename... Ts>
   struct index_list_if_builder_;
   
   // induction step
   template<int I, class Pred, unsigned... Is, typename T, typename... Ts>
   struct index_list_if_builder_<I,Pred,index_list<Is...>,T,Ts...>:
      If<Pred::template apply<T>::value
       , index_list_if_builder_<I+1,Pred,index_list<Is...,I>,Ts...>
       , index_list_if_builder_<I+1,Pred,index_list<Is...>  ,Ts...> 
       >
   { 
   };
   
   // base step
   template<int I, class Pred, class Index>
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

template<class Pred, typename... Ts>
using index_list_if 
   = typename detail::index_list_if_builder<Pred,Ts...>::type;

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_INDEX_H_INCLUDED */
