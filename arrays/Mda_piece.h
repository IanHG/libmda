#ifndef LIBMDA_MDA_PIECE_H
#define LIBMDA_MDA_PIECE_H

#include "Mda_i.h"
#include "Requesting.h"

namespace libmda
{
namespace arrays
{
namespace mda_impl
{
namespace detail
{
template<size_t N, size_t M> struct pow
{ static const int value = N*pow<N,M-1>::value; };
template<size_t N> struct pow<N,0>
{ static const int value = 1; };

template<size_t N, size_t M>
constexpr size_t Pow()
{ return pow<N,M>::value; }

template<size_t N, size_t M> struct piece_index_help
{
   template<class T, class... U>
   static const T apply(T t, U... u)
   { return Pow<M,N>()*t+piece_index_help<N-1,M>::apply(u...); }
};

template<size_t M> struct piece_index_help<0,M>
{
   template<class T>
   static const T apply(T t)
   { return Pow<M,0>()*t; }
};

} // namespace detail

template<size_t N, typename T, typename U, size_t M>
class Mda_piece: public Mda_i<Mda_piece<N,T,U,M>,N,T,U>
{
   public:
      typedef T value_type;
      typedef U size_type;
      static const int order  = N;
      static const int num_elem = M;
      
      // operator()
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type&       operator()(ints... i)       { return at(i...); }
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type const& operator()(ints... i) const { return at(i...); }
      
      // at()
      template<typename... ints>
      value_type&       at(ints... i)       { return m_ptr[m_slice.index(i...)]; }
      template<typename... ints>
      value_type const& at(ints... i) const { return m_ptr[m_slice.index(i...)]; }
      
      // size() and extent()
      constexpr size_type size() const { return detail::Pow<M,N>(); }
      template<size_t D, iEnable_if<D<N> = 0>
      constexpr size_type extent()  const { return M; }

      Mda_piece(): m_slice(), m_ptr() { }
      Mda_piece& operator=(const Mda_piece& a_mda)
      { MDACopy((*this),a_mda); return *this; }
      using Mda_i<Mda_piece<N,T,U,M>,N,T,U>::operator=;
   private:
      class Slice
      {
         public:
            template<typename... ints>
                     //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
                     //utility::Requesting_elem<order,size_type,ints...> = 0>
            size_type index(ints... i) const
            { return detail::piece_index_help<N-1,M>::apply(i...); }
      };
      
      Slice      m_slice;
      value_type m_ptr[M*N];
};

} // namespace mda_impl
} // namespace arrays
} // namespace mda_impl

#endif /* LIBMDA_MDA_PIECE_H */
