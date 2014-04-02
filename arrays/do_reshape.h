#ifndef LIBMDA_ARRAYS_DO_RESHAPE_H_INCLUDED
#define LIBMDA_ARRAYS_DO_RESHAPE_H_INCLUDED

#include <tuple>
#include "Mda_slice.h"

namespace libmda
{
namespace arrays
{
namespace detail
{

struct do_reshape_impl
{
   template<size_t O, size_t P, class Tuple>
   void operator()(const Mda_slice<O>& in, Mda_slice<P>& out, const Tuple& t)
   {
      
   }
};

} /* namespace detail */

template<size_t N, size_t N, class... Is>
void do_reshape(const Mda_slice<N>& in, Mda_slice<M>& out, Is... is)
{
   detail::do_reshape_impl()(in,out,std::forward_as_tuple(is...));
   out.start() = in.start();
   out.init_size();

   // sanity check
   assert(out.size() == in.size());
}

} /* namespace arrays */
} /* namespace libmda */

#endif /* LIBMDA_ARRAYS_DO_RESHAPE_H_INCLUDED */
