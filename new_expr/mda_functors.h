#ifndef LIBMDA_VECTOR_FUNCTORS_H_INCLUDED
#define LIBMDA_VECTOR_FUNCTORS_H_INCLUDED

#include "../iblas/igemm.h"
#include "../iblas/iaxpy.h"

namespace libmda
{
namespace expr
{

struct mda_functor_base
{
};

template<class T1, class T2>
struct mda_functor_plus_equal: public mda_functor_base
{
   static_assert(T1::order == T2::order, "not same order");

   T1& operator()(T1& t1, const T2& t2)
   {
      int incx = 1;
      int incy = 1;
      int size = t1.size();
      double alpha = 1.0;
      daxpy_(&size,&alpha,t1.data(),&incx,t2.data(),&incy);
      return t1;
   }
};

} /* namespace expr */
} /* namespace libmda */

#endif /* LIBMDA_VECTOR_FUNCTORS_H_INCLUDED */
