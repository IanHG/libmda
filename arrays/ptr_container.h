#ifndef LIBMDA_ARRAYS_POINTER_CONTAINER_H_INCLUDED
#define LIBMDA_ARRAYS_POINTER_CONTAINER_H_INCLUDED

#include<tuple>

namespace libmda
{
namespace arrays
{

namespace detail
{

template<size_t N, size_t M>
struct ptr_container_pos_impl
{
   template<class Tuple, class I>
   size_t operator()(const Tuple& t, I i) const
   {
      if(i<std::get<N>(t))
      {
         return N;
      }
      else
      {
         return ptr_container_pos_impl<N+1,M>()(t,i);
      }
   }
};

template<size_t M>
struct ptr_container_pos_impl<M,M>
{
   template<class Tuple, class I>
   size_t operator()(const Tuple& t, I i) const
   {
      return M;
   }
};

template<class Tuple>
size_t ptr_container_pos(const Tuple& s, i)
{
   return ptr_container_pos_impl<0,std::tuple_size<Tuple>::value-1>()(s,i);
}

} /* namespace detail */

struct ptr_container
{
   std::tuple<> _start;
   std::tuple<> _ptrs;

   auto operator[](int i)
   {
        
   }
}

} /* namespace arrays */
} /* namespace arrays */

#endif /* LIBMDA_ARRAYS_POINTER_CONTAINER_H_INCLUDED */
