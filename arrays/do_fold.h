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

struct do_fold_last_impl
{
   template<size_t O, size_t P, class T>
   void operator()(const Mda_slice<O>& in, Mda_slice<P>& out, T t)
   {
      for(size_t i = 0 ; i<O; ++i)
         out.extents()[i] = in.extents()[i];
      out.extents()[O] = out.extents()[O-1]/t;
      out.extents()[O-1] = t;
      out.init_strides();
   }
};

} /* namespace detail */

template<size_t I, size_t O, class T>
size_t do_fold_last(const Mda_slice<I>& in, Mda_slice<O>& out, T t)
{
   return detail::do_fold_last_impl()(in,out,t);
}

} /* namespace arrays */
} /* namespace libmda */

#endif /* LIBMDA_ARRAYS_DO_SLICE_H_INCLUDED */
