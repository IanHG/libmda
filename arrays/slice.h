#ifndef LIBMDA_ARRAYS_SLICE_H_INCLUDED
#define LIBMDA_ARRAYS_SLICE_H_INCLUDED

#include<tuple>
#include "../meta/index_list.h"
#include "../util/nth_value_of.h"
#include "../util/enforce.h"

namespace libmda
{
namespace arrays
{

namespace detail
{

template<size_t N>
struct multi_slice_index_impl
{
   template<class S, class Tuple>
   S operator()(const S* l, const S* s, S ll, const Tuple& t)
   {
      return s[N]*std::get<N>(t)*ll + multi_slice_index_impl<N-1>()(l,s,ll*l[N],t);
   }
};

template<>
struct multi_slice_index_impl<0>
{
   template<class S, class Tuple>
   S operator()(const S* l, const S* s, S ll, const Tuple& t)
   {
      return s[0]*std::get<0>(t)*ll;
   }
};

template<class S, class... Is>
S multi_slice_index(const S* l, const S* s, Is... is)
{
   return multi_slice_index_impl<sizeof...(Is)-1>()(l,s,size_t(1),std::forward_as_tuple(is...));  
};

} // namespace detail

//
// multi slice
//
template<size_t N>
struct multi_slice
{
   using size_type = size_t;
   static constexpr size_t order = N;

   const size_type m_start[N];
   const size_type m_length[N];
   const size_type m_stride[N];

   template<class... Is
          , util::iEnforce<sizeof...(Is) == N> = 0
          >
   size_type operator()(Is... is) const
   {
      return m_start + detail::multi_slice_index(m_length,m_stride,is...);
   };
   
   // actual c-tor
   template<unsigned... Is1
          , unsigned... Is2
          , unsigned... Is3
          , class... Ss
          >
   explicit multi_slice(meta::index_list<Is1...>
                      , meta::index_list<Is2...>
                      , meta::index_list<Is3...>
                      , Ss... ss
                      ) : m_start{static_cast<size_type>(util::nth_value_of<Is1>(ss...))...}
                        , m_length{static_cast<size_type>(util::nth_value_of<Is2>(ss...))...}
                        , m_stride{static_cast<size_type>(util::nth_value_of<Is3>(ss...))...}
   {
   }

   // delegating c-tor
   template<class... Ss
          //, util::iEnforce<sizeof...(Ss) == 3*N> = 0
          >
   explicit multi_slice(Ss... ss):
      multi_slice(meta::index_range<0,N>()
                , meta::index_range<N,2*N>()
                , meta::index_range<2*N,3*N>()
                , ss...
                )
   {
   }
   
   // deleted opers
   explicit multi_slice() = delete;
   explicit multi_slice(const multi_slice&) = delete;
   multi_slice& operator=(const multi_slice&) = delete;
};

//
// single slice
//
struct slice: multi_slice<1>
{
   using size_type = size_t;
   explicit slice(size_type st, size_type l, size_type s):
      multi_slice<1>(st,l,s)
   {
   }
};

} // namespace arrays
} // namespace libmda

#endif /*LIBMDA_ARRAYS_SLICE_H_INCLUDED */
