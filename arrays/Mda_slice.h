#ifndef LIBMDA_MDA_SLICE_H
#define LIBMDA_MDA_SLICE_H

#include<iostream>
#include<array>
#include<initializer_list>

#include "../metaprog/std_wrappers.h"
#include "../metaprog/check_type_.h"
#include "../metaprog/index.h"
#include "../utility/sequence.h"
#include "../utility/nth_value_of.h"


namespace libmda
{
namespace arrays
{
namespace mda_impl
{
namespace detail
{

// helper to initialize size
struct init_size 
{
   template<typename head, typename... tail>
   static head apply(head h, tail... t)
   { return h*init_size::apply(t...); }

   template<typename head>
   static head apply(head h)
   { return h; }
};

// helper to init strides to 1
template<typename ii>
constexpr ii ones_for(ii i)
{ return 1; }

// helper to do index calculation (think about design...)
template<size_t N, size_t M>
struct index_help
{
   template<class T, class U, class... V>
   static U apply(const T& t, U u, V... v)
   { return t[N]*u+index_help<N+1,M>::apply(t,v...); }
};

template<size_t N>
struct index_help<N,N>
{
   template<class T>
   static size_t apply(const T& t)
   { return 0; }
};

template<size_t N, size_t M, typename size_type>
struct multiply_impl
{
   static size_type apply(const utility::sequence<N,size_type>& seq)
   {
      return seq.template get<M>()*multiply_impl<N,M+1,size_type>::apply(seq);
   }
};

template<size_t N, typename size_type>
struct multiply_impl<N,N,size_type>
{
   static size_type apply(const utility::sequence<N,size_type>& seq)
   {
      return 1;
   }
};

template<size_t N, typename size_type>
inline size_type multiply(const utility::sequence<N,size_type>& seq)
{
   return multiply_impl<N,0,size_type>::apply(seq);
}

template<int N>
struct strides_impl
{
   template<typename... Ts>
   static size_t apply(Ts&&... ts)
   {
      return utility::nth_value_of<N-1>(ts...)*strides_impl<N-1>::apply(ts...);
   }
};

template<>
struct strides_impl<0>
{
   template<typename... Ts>
   static size_t apply(Ts&&... ts)
   {
      return 1;
   }
};

template<int N, typename... Ts>
size_t strides(Ts&&... ts)
{
   return strides_impl<N>::apply(std::forward<Ts>(ts)...);
};

} // namespace detail

template<size_t N, typename U=size_t>
class Mda_slice
{
   using size_type = U;
   static const int order = N;
   
   public:
      template<unsigned... Is1
             //, unsigned... Is2
             , typename... Ts>
      Mda_slice(metaprog::index_list<Is1...> const& i1
              //, metaprog::index_list<Is2...> const& i2
              , size_type a_start
              , Ts&&... ts): m_start  {a_start}
                           , m_extents{utility::nth_value_of<Is1>(ts...)...}
                           , m_size   {detail::multiply(m_extents)}
                           , m_strides{detail::strides<Is1>(ts...)...}
      { 
      };
      
      // delegating contructor
      template<typename... Ts
             , typename std::enable_if<sizeof...(Ts) == 2*N,void*>::type = nullptr
             >
      Mda_slice(size_type a_start, Ts&&... ts):
         Mda_slice(metaprog::index_range<0,N>()
                 //, metaprog::index_range<N,2*N>()
                 , std::forward<size_type>(a_start)
                 , std::forward<Ts>(ts)...)
      {
      };
      
      // get index
      template<typename... ints,
               iEnable_if<metaprog::check_type_and_size_<N,size_type,ints...>::value > = 0>
      size_type index(const ints... i) const
      {
         // return index
         return m_start + detail::index_help<0,N>::apply(m_strides,i...);
      }
      
      // get total size
      size_t size() const { return m_size; }
      // get extent in dimension
      template<size_t M, iEnable_if<M<N> = 0> 
      size_type extent() const { return m_extents[M]; }

      utility::sequence<N,size_type> const& extents() const { return m_extents; }
      utility::sequence<N,size_type> const& strides() const { return m_strides; }

   private:
      size_type m_start;                        // start offset
      utility::sequence<N,size_type> m_extents; // dimension extents
      
      size_type m_size;                         // total number of elements
      utility::sequence<N,size_type> m_strides; // offset for each dimension
};

}// namespace mda_impl
}// namespace arrays
}// namespace libmda

#endif /* LIBMDA_MDA_SLICE_H */
