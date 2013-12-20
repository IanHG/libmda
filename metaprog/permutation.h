#ifndef LIBMDA_PERMUTATION_H
#define LIBMDA_PERMUTATION_H

#include "mpsize_t.h"
#include "../metaprog/get_type_n_.h"
//#include "../metaprog/type_tuple_.h"
#include "iterator.h"
#include "tuple.h"
#include "permute.h"
#include "unique.h"

namespace libmda
{
namespace metaprog
{
/**************************/
// forward declaration
/**************************/
template<class... N> struct permutation_;
struct permutation_tag { };

namespace detail
{
/**************************/
// is this a valid permutation
/**************************/
template<size_t N, size_t M, size_t... O>
struct permutation_is_valid
{
   static const bool value = M<N &&  // M must be less than total number of elems
                             i_unique<M,O...>::value &&  // M must be unique
                             permutation_is_valid<N,O...>::value; // need to validate rest of elems
};
template<size_t N, size_t M>
struct permutation_is_valid<N,M>
{ static const bool value = M<N && i_unique<M>::value; };

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
template<class    T, class    U> struct permute_permutation_impl;
template<class... T, class... U> struct permute_permutation_impl<permutation_<T...>, permutation_<U...> >
{
   using type = permutation_<mpsize_t<permutation_<T...>::template index<U::value>()>...>;
};
template<> struct permute_impl<permutation_tag>
{
   template<class T, class U> struct apply: permute_permutation_impl<T,U> { };
};

} // namespace detail

template<class... N>
class permutation_
{
   public:
      using tag  = permutation_tag;
      using This = permutation_<N...>;
      static const int order = sizeof...(N);

      template<size_t M>
      static constexpr size_t index() { return get_type_n_<M,N...>::type::value; }
      template<size_t M>
      using At = typename get_type_n_<M,N...>::type;
      
      template<size_t... M>
      using Permute = permute<This,permutation_<mpsize_t<M>...> >;

      //using Begin = iterator<This,0>;
      //using End   = iterator<This,order>;
   
   private:
      // assert if it a valid permutation
      static const bool valid = detail::permutation_is_valid<order,N::value...>::value;
      static_assert(valid, "permutation not valid");
};

// interface !
template<size_t... N> using permutation = permutation_< mpsize_t<N> ...>;

} // namespace utility
} // namespace libmda

#endif /* LIBMDA_PERMUTATION_H */
