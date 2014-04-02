#ifndef LIBMDA_ARRAYS_DO_SLICE_H_INCLUDED
#define LIBMDA_ARRAYS_DO_SLICE_H_INCLUDED

#include <tuple>
#include "Mda_slice.h"

namespace libmda
{
namespace arrays
{
namespace detail
{

template<size_t N, size_t O>
struct do_extents_impl
{
   template<size_t M, class S>
   void operator()(Mda_slice<M>& out, const S& s)
   {
      out.extents()[N+O] = s.m_length[O] - s.m_start[O] + 1;
      do_extents_impl<N,O-1>()(out,s);
   }
};

template<size_t N>
struct do_extents_impl<N,0>
{
   template<size_t M, class S>
   void operator()(Mda_slice<M>& out, const S& s)
   {
      out.extents()[N] = s.m_length[0] - s.m_start[0] + 1;
   }
};

//template<size_t N>
//struct do_strides_impl
//{
//   void operator()(Mda_slice<M>& out, const S& s)
//   {
//
//   }
//}

template<size_t N, size_t M, size_t O, size_t P, class Tuple>
size_t do_slice_impl2(const Mda_slice<O>& in, Mda_slice<P>& out, const Tuple& t)
{
   //out.m_extents[M] = std::get<N>(t).m_length[0] - std::get<N>(t).m_start + 1;
   do_extents_impl<M,std::decay<decltype(std::get<N>(t))>::type::order-1>()(out,std::get<N>(t));
   out.m_strides[M] = in.m_strides[N];
   return std::get<N>(t).m_start[0]*in.m_strides[N];
}

template<size_t N, size_t M>
struct do_slice_impl
{
   template<size_t O, size_t P, class Tuple>
   size_t operator()(const Mda_slice<O>& in, Mda_slice<P>& out, const Tuple& t)
   {
      size_t m = do_slice_impl2<N,M>(in,out,t);
      return m + do_slice_impl<N-1,M-(std::decay<decltype(std::get<N>(t))>::type::order)>()(in,out,t);
   }
};

template<>
struct do_slice_impl<0,0>
{
   template<size_t O, size_t P, class Tuple>
   size_t operator()(const Mda_slice<O>& in, Mda_slice<P>& out, const Tuple& t)
   {
      return do_slice_impl2<0,0>(in,out,t);
   }
};

} /* namespace detail */

template<size_t N, size_t M, class... Ss>
size_t do_slice(const Mda_slice<N>& in, Mda_slice<M>& out, Ss&&... ss)
{
   static_assert(sizeof...(Ss) == N,"dimension does not fit");
   return detail::do_slice_impl<N-1,M-1>()(in,out,std::forward_as_tuple(ss...));
}

} /* namespace arrays */
} /* namespace libmda */

#endif /* LIBMDA_ARRAYS_DO_SLICE_H_INCLUDED */
