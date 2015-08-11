#ifndef LIBMDA_IMDA_ASSIGN_SCALAR_H_INCLUDED
#define LIBMDA_IMDA_ASSIGN_SCALAR_H_INCLUDED

#include "imda_access.h"
#include "../util/for_loop_expand.h"

namespace libmda
{

namespace imda
{

// make structs with operators:
// =, +=, -=, *=, /=
// for element by element operations
// these are used by assign mixins
#define LIBMDA_CREATE_EQUALOPER_SCALAR(NAME,OP) \
struct NAME \
{ \
   template<class V, class U, class... Is> \
   static void apply(V& v, const U& u, const Is... is) \
   { v.at(is...) OP u; } \
  \
   /*template<typename V, typename U, class meta::Enable_if<util::has_vec_at<V>::value && util::has_vec_at<U>::value> > */\
   /*static void apply_vec(V& v, const U& u, const typename V::size_type i) */\
   /*{ v.vec_at(i) OP u.vec_at(i); }*/ \
};

LIBMDA_CREATE_EQUALOPER_SCALAR(op_equal_scal,=)
LIBMDA_CREATE_EQUALOPER_SCALAR(op_plus_equal_scal,+=)
LIBMDA_CREATE_EQUALOPER_SCALAR(op_sub_equal_scal,-=)
LIBMDA_CREATE_EQUALOPER_SCALAR(op_mult_equal_scal,*=)
LIBMDA_CREATE_EQUALOPER_SCALAR(op_div_equal_scal,/=)
#undef LIBMDA_CREATE_EQUALOPER_SCALAR

//
// mixin that provides = operator overloads
//
template<class A>
struct elem_assign_scalar: A
{
   //
   // operator=
   //
   template<class B
          , class C = A
          >
   //auto operator=(B&& v)
   auto assign_scalar(B&& v)
      -> decltype(std::declval<C>().self())
   {
      util::for_loop_expand<op_equal_scal>::apply((*this),std::forward<B>(v));
      //util::for_each_elem(equal_functor(),(*this),v);
      return this->self();
   }
};

//
// mixin that provides += operator overloads
//
template<class A>
struct elem_assign_add_scalar: A
{
   template<class B
          , class C = A
          >
   auto operator+=(const B& v)
      -> decltype(std::declval<C>().self())
   {
      util::for_loop_expand<op_plus_equal_scal>::apply((*this),v);
      return this->self();
   }
};

//
// mixin that provides -= operator overloads
//
template<class A>
struct elem_assign_sub_scalar: A
{
   template<class B
          , class C = A
          >
   auto operator-=(const B& v)
      -> decltype(std::declval<C>().self())
   {
      util::for_loop_expand<op_sub_equal_scal>::apply((*this),v);
      return this->self();
   }
};

//
// mixin that provides *= operator overload
//
template<class A>
struct elem_assign_mul_scalar: A
{
   template<class B
          , class C = A
          >
   auto operator*=(const B& v)
      -> decltype(std::declval<C>().self())
   {
      util::for_loop_expand<op_mult_equal_scal>::apply((*this),v);
      return this->self();
   }
};
   
//
// mixin that provides /= operator overload
//
template<class A>
struct elem_assign_div_scalar: A
{
   template<class B
          , class C = A
          >
   auto operator/=(const B& v)
      -> decltype(std::declval<C>().self())
   {
      util::for_loop_expand<op_div_equal_scal>::apply((*this),v);
      return this->self();
   }
};

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_ASSIGN_SCALAR_H_INCLUDED */
