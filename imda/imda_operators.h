#ifndef LIBMDA_IMDA_OPERATORS_H_INCLUDED
#define LIBMDA_IMDA_OPERATORS_H_INCLUDED

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
#define LIBMDA_CREATE_EQUALOPER(NAME,OP) \
struct NAME \
{ \
   template<class V, class U, class... Is> \
   static void apply(V&& v, U&& u, Is... is) \
   { \
      v.at(is...) OP u.at(is...); \
   } \
 \
   /*template<typename V, typename U, class meta::Enable_if<util::has_vec_at<V>::value && util::has_vec_at<U>::value> > */\
   /*static void apply_vec(V& v, const U& u, const typename V::size_type i) */\
   /*{ v.vec_at(i) OP u.vec_at(i); }*/ \
};

LIBMDA_CREATE_EQUALOPER(op_equal,=)
LIBMDA_CREATE_EQUALOPER(op_plus_equal,+=)
LIBMDA_CREATE_EQUALOPER(op_sub_equal,-=)
LIBMDA_CREATE_EQUALOPER(op_mult_equal,*=)
LIBMDA_CREATE_EQUALOPER(op_div_equal,/=)
#undef LIBMDA_CREATE_EQUALOPER

//
// functors for new framework
//
//
#define LIBMDA_CREATE_EQUALFUNCTOR(NAME,OP) \
struct NAME \
{ \
   template<class V, class U, class... Is> \
   void operator()(V&& v, U&& u, Is... is) const \
   { \
      v.at(is...) OP u.at(is...); \
   } \
};

LIBMDA_CREATE_EQUALFUNCTOR(equal_functor,=)
LIBMDA_CREATE_EQUALFUNCTOR(add_equal_functor,+=)
LIBMDA_CREATE_EQUALFUNCTOR(sub_equal_functor,-=)
LIBMDA_CREATE_EQUALFUNCTOR(mul_equal_functor,*=)
LIBMDA_CREATE_EQUALFUNCTOR(div_equal_functor,/=)
#undef LIBMDA_CREATE_EQUALFUNCTOR

#define LIBMDA_CREATE_SCALEEQUALFUNCTOR(NAME,OP) \
template<class T = double> \
struct NAME \
{ \
   T _scalar; \
   \
   explicit NAME(T t): _scalar{t} \
   { \
   } \
   \
   template<class V, class U, class... Is> \
   void operator()(V&& v, U&& u, Is... is) const \
   { \
      v.at(is...) OP _scalar*u.at(is...); \
   } \
};

LIBMDA_CREATE_SCALEEQUALFUNCTOR(scale_equal_functor,=)
LIBMDA_CREATE_SCALEEQUALFUNCTOR(scale_add_equal_functor,+=)
LIBMDA_CREATE_SCALEEQUALFUNCTOR(scale_sub_equal_functor,-=)
LIBMDA_CREATE_SCALEEQUALFUNCTOR(scale_mul_equal_functor,*=)
LIBMDA_CREATE_SCALEEQUALFUNCTOR(scale_div_equal_functor,/=)
#undef LIBMDA_CREATE_SCALEEQUALFUNCTOR



} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_OPERATORS_H_INCLUDED */
