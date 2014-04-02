#ifndef LIBMDA_MDA_SLICE_H
#define LIBMDA_MDA_SLICE_H

#include<iostream>
#include<array>
#include<initializer_list>
#include<tuple>

#include "../meta/std_wrappers.h"
#include "../meta/check_type_.h"
#include "../meta/index_list.h"
#include "../util/sequence.h"
#include "../util/nth_value_of.h"


namespace libmda
{
namespace arrays
{
template<size_t N, class U = size_t>
class Mda_slice;

namespace detail
{
template<size_t L, size_t M, size_t O, size_t P, class S>
size_t do_slice_impl2(const Mda_slice<O>&, Mda_slice<P>&, const S&);

// helper to initialize size
struct init_size 
{
   template<typename head, typename... tail>
   static head apply(head h, tail... t)
   { 
      return h*init_size::apply(t...); 
   }

   template<typename head>
   static head apply(head h)
   { 
      return h; 
   }
};

// helper to init strides to 1
template<typename ii>
constexpr ii ones_for(ii i)
{ 
   return 1; 
}

// helper to do index calculation (think about design...)
template<size_t N>
struct index_help
{
   template<class S, class Tuple>
   static size_t apply(const S& s, const Tuple& t)
   { 
      return s[N]*std::get<N>(t)+index_help<N-1>::apply(s,t); 
   }
};

template<>
struct index_help<0>
{
   template<class S, class Tuple>
   static size_t apply(const S& s, const Tuple& t)
   { 
      return s[0]*std::get<0>(t); 
   }
};

template<size_t N, size_t M, typename size_type>
struct multiply_impl
{
   static size_type apply(const util::sequence<N,size_type>& seq)
   {
      return seq.template get<M>()*multiply_impl<N,M+1,size_type>::apply(seq);
   }
};

template<size_t N, typename size_type>
struct multiply_impl<N,N,size_type>
{
   static size_type apply(const util::sequence<N,size_type>& seq)
   {
      return 1;
   }
};

template<size_t N, typename size_type>
inline size_type multiply(const util::sequence<N,size_type>& seq)
{
   return multiply_impl<N,0,size_type>::apply(seq);
}

//
//
//
template<int N>
struct strides_impl
{
   template<typename... Ts>
   static size_t apply(Ts&&... ts)
   {
      return util::nth_value_of<N-1>(ts...)*strides_impl<N-1>::apply(ts...);
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

template<size_t N, size_t M>
struct init_strides_impl
{
   template<class S>
   void operator()(const S& e, S& s)
   {
      init_strides_impl<N+1,M>()(e,s);
      s[N] = e[N+1]*s[N+1];
   }
};

template<size_t N>
struct init_strides_impl<N,N>
{
   template<class S>
   void operator()(const S& e, S& s)
   {
      s[N] = 1;
   }
};

template<size_t N, class S>
void init_strides(const S& e, S& s)
{
   init_strides_impl<0,N-1>()(e,s);
}

} // namespace detail

template<size_t N, class U>
class Mda_slice
{
   using size_type = U;
   static const int order = N;
   
   private:
      template<unsigned... Is1
             //, unsigned... Is2
             , typename... Ts
             >
       Mda_slice(meta::index_list<Is1...>
               //, meta::index_list<Is2...>
               , size_type a_start
               , Ts&&... ts
               ): m_start  {a_start}
                , m_extents{util::nth_value_of<Is1>(ts...)...}
                , m_size   {detail::multiply(m_extents)}
                //, m_strides{detail::strides<N-1-Is1>(ts...)...}
      { 
         detail::init_strides<N>(m_extents,m_strides);
      };
      
      Mda_slice& operator=(const Mda_slice&) = delete;
      
      template<size_t L, size_t M, size_t O, size_t P, class S>
      friend size_t detail::do_slice_impl2(const Mda_slice<O>&, Mda_slice<P>&, const S&);

   public:
      // delegating contructor
      template<typename... Ts
             //, meta::iEnable_if<sizeof...(Ts) == 2*N> = 0
             >
      Mda_slice(size_type&& a_start, Ts&&... ts):
         Mda_slice(meta::index_range<0,N>()
                 //, meta::index_range<N,2*N>()
                 , std::forward<size_type>(a_start)
                 , std::forward<Ts>(ts)...
                 )
      {
      }
      
      // default c-tor
      explicit Mda_slice() = default;

      //
      explicit Mda_slice(const Mda_slice&) = default;
      Mda_slice(Mda_slice&&) = default;
      
      // get index
      template<typename... ints
             , iEnable_if<meta::check_type_and_size_<N,size_type,ints...>::value > = 0
             >
      size_type index(const ints... i) const
      {
         // return index
         return m_start + detail::index_help<N-1>::apply(m_strides,std::forward_as_tuple(i...));
      }
      
      // get total size
      size_type size() const 
      { 
         return m_size; 
      }
      
      // get extent in dimension
      template<size_t M
             , iEnable_if<M<N> = 0
             >
      size_type extent() const 
      { 
         return m_extents[M]; 
      }
      
      //
      // get extents
      //
      util::sequence<N,size_type>& extents()
      { 
         return m_extents; 
      }
      // const version
      util::sequence<N,size_type> const& extents() const 
      { 
         return m_extents; 
      }
      
      //
      // get strides
      // 
      util::sequence<N,size_type>& strides()
      { 
         return m_strides; 
      }
      // const version
      util::sequence<N,size_type> const& strides() const 
      { 
         return m_strides; 
      }

      //
      //
      //
      size_type& start()
      {
         return m_start;
      }
      //
      size_type const& start() const
      {
         return m_start;
      }

      template<size_t M, class V>
      friend std::ostream& operator<<(std::ostream&,const Mda_slice<M,V>&);

      //
      //
      //
      void init_size()
      {
         m_size = detail::multiply(m_extents);
      }

      void init_strides()
      {
         detail::init_strides<N>(m_extents,m_strides);
      }
      
      template<class P>
      void permute()
      {
         m_extents.template permute<P>();
         m_strides.template permute<P>();
      }

   private:
      size_type m_start;                     // start offset
      util::sequence<N,size_type> m_extents; // dimension extents
      
      size_type m_size;                      // total number of elements
      util::sequence<N,size_type> m_strides; // offset for each dimension
};

template<size_t N, class U>
std::ostream& operator<<(std::ostream& a_ostream, const Mda_slice<N,U>& mda_slice)
{
   a_ostream << "Mda_slice output: \n"
             << "   start   : " << mda_slice.m_start << "\n"
             << "   extents : " << mda_slice.m_extents << "\n"
             << "   size    : " << mda_slice.m_size << "\n"
             << "   strides : " << mda_slice.m_strides << "\n";
   return a_ostream;
}

}// namespace arrays
}// namespace libmda

#endif /* LIBMDA_MDA_SLICE_H */
