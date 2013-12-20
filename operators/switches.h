#ifndef LIBMDA_OPERATORS_SWITCHES_H
#define LIBMDA_OPERATORS_SWITCHES_H

#include<type_traits>
#include "expression_binary_operators.h"
#include "../expr/take_out_types.h"

namespace libmda
{
namespace expr
{

template<class L, class R, template<class, class> class Op>
class binary_expression;

template<class A, template<class> class Op>
class unary_expression;

} // namespace expr
} // namespace libmda

namespace libmda
{
namespace operators
{

#ifdef __clang__
#pragma clang diagnostic push                           // disable some clang 
#pragma clang diagnostic ignored "-Wundefined-internal" // compiler warnings 
#pragma clang diagnostic push                           // as they are not
#pragma clang diagnostic ignored "-Wundefined-inline"   // needed here
#endif /* __clang__ */

/**
 * make general is "operator-able" switches
 **/
#define LIBMDA_CREATE_BINARY_SWITCH(NAME) \
template<class A> \
class is_##NAME \
{ \
   template<class B, \
            template<class, class, template<class, class> class> class bin, \
            template<class, class> class op> \
   static constexpr std::true_type  test(libmda_##NAME<op,bin,B>&); \
   static constexpr std::false_type test(...); \
   static constexpr A makeA(); \
   typedef decltype(test(makeA())) type;\
   public: \
      static const bool value = type::value; \
};
   
LIBMDA_CREATE_BINARY_SWITCH(addable)
LIBMDA_CREATE_BINARY_SWITCH(subtractable)
LIBMDA_CREATE_BINARY_SWITCH(multiplicable)
LIBMDA_CREATE_BINARY_SWITCH(divisable)
#undef LIBMDA_CREATE_BINARY_SWITCH

/**
 * Make is "operator-able" switches for binary and unary expressions
 **/
#define LIBMDA_CREATE_EXPR_BINARY_SWITCHES(NAME) \
template<class L, class R, template<class, class> class Op> \
struct is_##NAME<libmda::expr::binary_expression<L,R,Op> > \
{ static const bool value = is_##NAME<typename expr::take_out_types<L,R>::type>::value; }; \
 \
template<class A, template<class> class Op> \
struct is_##NAME<libmda::expr::unary_expression<A,Op> > \
{ static const bool value = is_##NAME<A>::value; };

LIBMDA_CREATE_EXPR_BINARY_SWITCHES(addable)
LIBMDA_CREATE_EXPR_BINARY_SWITCHES(subtractable)
LIBMDA_CREATE_EXPR_BINARY_SWITCHES(multiplicable)
LIBMDA_CREATE_EXPR_BINARY_SWITCHES(divisable)
#undef LIBMDA_CREATE_EXPR_BINARY_SWITCHES

#ifdef __clang__
#pragma clang diagnostic pop // enable the compiler warning again
#pragma clang diagnostic pop // ...
#endif /* __clang__ */

#define LIBMDA_CREATE_SWITCH_INTERFACE(NAME) \
template<class A> \
constexpr bool Is_##NAME() \
{ return is_##NAME<A>::value; }

LIBMDA_CREATE_SWITCH_INTERFACE(addable)
LIBMDA_CREATE_SWITCH_INTERFACE(subtractable)
LIBMDA_CREATE_SWITCH_INTERFACE(multiplicable)
LIBMDA_CREATE_SWITCH_INTERFACE(divisable)
#undef LIBMDA_CREATE_SWITCH_INTERFACE

} // namespace operators

// make interface functions available in namespace libmda
using operators::Is_addable;
using operators::Is_subtractable;
using operators::Is_multiplicable;
using operators::Is_divisable;

} // namespace libmda

#endif /* LIBMDA_OPERATORS_SWITCHES_H */
