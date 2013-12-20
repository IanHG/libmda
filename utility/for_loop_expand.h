#ifndef LIBMDA_UTILITY_FOR_LOOP_EXPAND_H_INCLUDED
#define LIBMDA_UTILITY_FOR_LOOP_EXPAND_H_INCLUDED

#include"../metaprog/loop.h"
#include"../metaprog/iterator.h"
#include"../metaprog/std_wrappers.h"

namespace libmda
{
namespace utility
{
/**
 * for loop expander
 **/
template<class N, class M, class Op>
struct for_loop_expand_impl
{
   template<class V, class... U> struct sub
   {
      template<typename... ints>
      static void apply(V& v, U&... u, const ints ...i)
      {
         using size_type = Size_type<V>;
         for(size_type dim_idx=0; dim_idx<v.template extent<deref<N>::value>(); ++dim_idx)
            for_loop_expand_impl<next<N>,M,Op>::template sub<V,U...>::apply(v,u...,i...,dim_idx);
      }
   };
};

template<class N, class Op>
struct for_loop_expand_impl<N,N,Op>
{
   template<class V, class... U> struct sub
   {
      template<typename... ints>
      static void apply(V& v, U&... u, const ints ...i) { Op::apply(v,u...,i...); }
   };
};

template<class Op>
struct for_loop_expand
{
   template<class V, class... U>
   static void apply(V& v, U&... u)
   { 
      using l = libmda::metaprog::loop<0,V::order>;
      for_loop_expand_impl<begin<l>,end<l>,Op>::template sub<V,U...>::apply(v,u...); 
   }
};

template<class Op, class dim>
struct for_loop_expand_dim
{
   template<class V, class... U>
   static void apply(V& v, U&... u)
   { 
      using l = dim;
      for_loop_expand_impl<begin<l>,end<l>,Op>::template sub<V,U...>::apply(v,u...); 
   }
};


template<class N, class M>
struct for_each_elem_impl
{
   template<class V, class... U> struct sub
   {
      template<class F, class... ints> static void apply(F&& f, V&& v, U&&... u, ints... i)
      {
         for(Size_type<Remove_reference<V> > idx=0; idx<v.template extent<deref<N>::value >(); ++idx)
            for_each_elem_impl<next<N>,M>::template sub<V,U...>::apply(std::forward<F>(f)
                                                                     , std::forward<V>(v)
                                                                     , std::forward<U>(u)...
                                                                     , i...
                                                                     , idx);
      }
   };
};

template<class N>
struct for_each_elem_impl<N,N>
{
   template<class V, class... U> struct sub
   {
      template<class F, class... ints> static void apply(F&& f, V&& v, U&&... u, ints... i)
      {
         f(v,u...,i...);
      }
   };
};



template<class F, class V, class... U>
void for_each_elem(F&& f, V&& v, U&&... u)
{
   using l = libmda::metaprog::loop<0,Remove_reference<V>::order>;
   for_each_elem_impl<begin<l>, end<l> >::template sub<V,U...>::apply(std::forward<F>(f)
                                                                    , std::forward<V>(v)
                                                                    , std::forward<U>(u)...);
}

/**
 * for loop expander end
 **/
} //namespace utility
} //namespace libmda

#endif /* LIBMDA_UTILITY_FOR_LOOP_EXPAND_H_INCLUDED */
