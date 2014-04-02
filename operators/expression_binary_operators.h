#ifndef LIBMDA_OPERATORS_EXPRESSION_BINARY_OPERATORS_H
#define LIBMDA_OPERATORS_EXPRESSION_BINARY_OPERATORS_H

#include "../util/empty_base.h"

namespace libmda
{
namespace expr
{

template<class A>
struct expression_base;

template<class L, class R, template<class, class> class Op>
struct binary_expression;

template<class A, template<class> class Op>
struct unary_expression;

} // namespace expr
} // namespace libmda

namespace libmda
{
namespace operators
{

// clean up macro when converged !
//
//
//
#define LIBMDA_CREATE_BINARY_OPERATOR(NAME,OP) \
template<template<class, class> class op \
       , template<class, class, template<class, class> class> class bin \
       , class A = util::empty_base \
       > \
struct NAME: public A \
{ \
   using base_type = A; \
}; \
\
template<class L \
       , class R \
       , template<class, class> class op \
       , template<class, class, template<class, class> class> class bin \
       > \
inline bin<NAME<op,bin,L>,NAME<op,bin,R>,op> \
operator OP(const NAME<op,bin,L>& a_lhs, const NAME<op,bin,R>& a_rhs) \
{ \
   return bin<NAME<op,bin,L>,NAME<op,bin,R>,op>(a_lhs, a_rhs); \
} 

LIBMDA_CREATE_BINARY_OPERATOR(libmda_addable,+)
LIBMDA_CREATE_BINARY_OPERATOR(libmda_subtractable,-)
LIBMDA_CREATE_BINARY_OPERATOR(libmda_multiplicable,*)
LIBMDA_CREATE_BINARY_OPERATOR(libmda_divisable,/)
#undef LIBMDA_CREATE_BINARY_OPERATOR

//
//
//
#define LIBMDA_CREATE_UNARY_OPERATOR(NAME,OP) \
template<template<class> class op \
       , template<class, template<class> class> class un \
       , class A = util::empty_base \
       > \
struct NAME : public A \
{ \
   using base_type = A; \
}; \
\
template<class A \
       , template<class> class op \
       , template<class, template<class> class> class un> \
inline un<NAME<op,un,A>, op> \
operator OP(const NAME<op,un,A>& a_arg) \
{ \
   return un<NAME<op,un,A>, op>(a_arg); \
}

LIBMDA_CREATE_UNARY_OPERATOR(libmda_unary_plus,+)
LIBMDA_CREATE_UNARY_OPERATOR(libmda_unary_minus,-)
#undef LIBMDA_CREATE_UNARY_OPERATOR

//
//
//
#define LIBMDA_CREATE_UNARY_FUNCTION(NAME,FUNC) \
template<template<class> class op \
       , template<class, template<class> class> class un \
       , class A = util::empty_base \
       > \
struct NAME : public A \
{ \
   using base_type = A; \
}; \
\
template<class A \
       , template<class> class op \
       , template<class, template<class> class> class un \
       > \
inline un<NAME<op,un,A>, op> \
FUNC(const NAME<op,un,A>& a_arg) \
{ \
   return un<NAME<op,un,A>, op>(a_arg); \
}

LIBMDA_CREATE_UNARY_FUNCTION(libmda_cosineable,cos)
LIBMDA_CREATE_UNARY_FUNCTION(libmda_sinusable,sin)
#undef LIBMDA_CREATE_UNARY_FUNCTION

//
//
//
#define LIBMDA_CREATE_SCALAR_BINARY_OPERATOR(NAME,OP) \
template<template<class, class> class op \
       , template<class, class, template<class, class> class> class bin \
       , class A = util::empty_base \
       > \
struct NAME: public A \
{ \
   using base_type = A; \
}; \
\
template<class L \
       , template<class, class> class op \
       , template<class, class, template<class, class> class> class bin \
       > \
inline bin<NAME<op,bin,L>,typename L::value_type,op> \
operator OP(const NAME<op,bin,L>& a_lhs, const typename L::value_type& a_rhs) \
{ \
   return bin<NAME<op,bin,L>,typename L::value_type,op>(a_lhs, a_rhs); \
} \
\
template<class R \
       , template<class, class> class op \
       , template<class, class, template<class, class> class> class bin \
       > \
inline bin<typename R::value_type,NAME<op,bin,R>,op> \
operator OP(const typename R::value_type& a_lhs, const NAME<op,bin,R>& a_rhs) \
{ \
   return bin<typename R::value_type,NAME<op,bin,R>,op>(a_lhs, a_rhs); \
} 

LIBMDA_CREATE_SCALAR_BINARY_OPERATOR(libmda_scalar_addable,+)
LIBMDA_CREATE_SCALAR_BINARY_OPERATOR(libmda_scalar_subtractable,-)
LIBMDA_CREATE_SCALAR_BINARY_OPERATOR(libmda_scalar_multiplicable,*)
LIBMDA_CREATE_SCALAR_BINARY_OPERATOR(libmda_scalar_divisable,/)
#undef LIBMDA_CREATE_SCALAR_BINARY_OPERATOR

//
//
//
/*template<class A>
struct libmda_assignable_to_scal : A { };

#define LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(OP) \
template<class A, iEnable_if<A::num_dim == 0> = 0> \
value_type operator OP(const typename A::value_type& a_scal, \
      const libmda_assignable_to_scal<A>& a_rhs) \
{ return a_scal OP a_rhs(); } \

//LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(=)
LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(+=)
LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(-=)
LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(*=)
LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR(/=)
#undef LIBMDA_CREATE_ASSIGN_TO_SCALAR_OPERATOR */


// the below should be moved !
//
//
//
template<template<class, class> class op_add
       , template<class, class> class op_sub 
       , template<class, class> class op_mult 
       , template<class, class> class op_div
       , class A
       >
struct expression_binary_operators:
   libmda_addable<op_add, libmda::expr::binary_expression,
   libmda_subtractable<op_sub, libmda::expr::binary_expression,
   libmda_multiplicable<op_mult, libmda::expr::binary_expression,
   libmda_divisable<op_div, libmda::expr::binary_expression,
   A
   > > > >
{ 
};

//
//
//
template<template<class> class op_plus
       , template<class> class op_minus
       , class A>
struct expression_unary_operators:
   libmda_unary_plus<op_plus, libmda::expr::unary_expression,
   libmda_unary_minus<op_minus, libmda::expr::unary_expression,
   A
   > >
{ 
};

//
//
//
template<template<class> class op_cos
       , template<class> class op_sin
       , class A>
struct expression_trigonometri_functions:
   libmda_cosineable<op_cos, libmda::expr::unary_expression,
   libmda_sinusable<op_sin, libmda::expr::unary_expression,
   A
   > >
{ 
};

//
//
//
template<template<class, class> class op_scal_add
       , template<class, class> class op_scal_sub
       , template<class, class> class op_scal_mult
       , template<class, class> class op_scal_div
       , class A>
struct expression_scalar_binary_operators:
   libmda_scalar_addable<op_scal_add, libmda::expr::binary_expression,
   libmda_scalar_subtractable<op_scal_sub, libmda::expr::binary_expression,
   libmda_scalar_multiplicable<op_scal_mult, libmda::expr::binary_expression,
   libmda_scalar_divisable<op_scal_div, libmda::expr::binary_expression,
   A
   > > > >
{ 
};
// move end !

} // namespace operators
} // namespace libmda

#endif /* LIBMDA_OPERATORS_EXPRESSION_BINARY_OPERATORS_H */
