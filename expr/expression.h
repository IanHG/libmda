#ifndef LIBMDA_EXPR_EXPRESSION_H
#define LIBMDA_EXPR_EXPRESSION_H

#include<utility>
#include<iostream>
#include<math.h>
#include"../interface.h"
#include"../metaprog/std_wrappers.h"
#include"../metaprog/check_type_.h"
#include"../utility/for_loop_expand.h"
#include"../utility/mixin_if.h"
#include"../utility/has_member.h"
#include"../operators/switches.h"
#include"take_out_types.h"
#include"../basic_using.h"
#include"char_expression.h"

namespace libmda
{
namespace expr
{

template<class A>
struct traits;

template<class A, class trait>
struct expression:          //// Need typedef nothing in these
   //libmda::expr::assignable_to_scalar<
   libmda::char_expr::char_expression_interface<
   libmda::operators::expression_scalar_binary_operators<operator_traits<A>::template oper_scal_add, operator_traits<A>::template oper_scal_sub, operator_traits<A>::template oper_scal_mult, operator_traits<A>::template oper_scal_div,
   utility::mixin_if<Is_addable<A>()      ,operators::libmda_addable<operator_traits<A>::template oper_scal_add, binary_expression,
   utility::mixin_if<Is_subtractable<A>() ,operators::libmda_subtractable<operator_traits<A>::template oper_scal_sub, binary_expression,
   utility::mixin_if<Is_multiplicable<A>(),operators::libmda_multiplicable<operator_traits<A>::template oper_scal_mult, binary_expression,
   utility::mixin_if<Is_divisable<A>()    ,operators::libmda_divisable<operator_traits<A>::template oper_scal_div, binary_expression,
   libmda::operators::expression_trigonometri_functions<operator_traits<A>::template oper_cos, operator_traits<A>::template oper_sin,
   libmda::operators::expression_unary_operators<operator_traits<A>::template oper_unary_plus, operator_traits<A>::template oper_unary_minus,
   libmda::operators::expression_binary_operators<operator_traits<A>::template oper_add, operator_traits<A>::template oper_sub, operator_traits<A>::template oper_mult, operator_traits<A>::template oper_div,
   expression_base<
   libmda::IMDAAccessComb<
   libmda::IMDAAccess<Value_access(),
   libmda::IMDADim<
   libmda::IMDASelf<
   A, trait
   > >  > >  > >  > >  > > > > > > > > > >,
   IMDABase
{ };

/**
 * binary expression
 **/
template<class L, class R, template<class, class> class Op>
class binary_expression:
   public expression<binary_expression<L,R,Op>, traits<binary_expression<L,R,Op> > >
{
   public:
      using traits_type = traits<binary_expression<L,R,Op> >;
      using value_type  = Value_type<traits_type>;
      using size_type   = Size_type<traits_type>;
      static const int order = Order<Op<L,R> >();
      
      //using base_type = expression<binary_expression<L,R,Op>, traits<binary_expression<L,R,Op> > >;
   private:
      const L& m_lhs;
      const R& m_rhs;

   public:
      // constructor
      binary_expression(const L& a_lhs, const R& a_rhs): m_lhs(a_lhs)
                                                       , m_rhs(a_rhs) { };
      
      // at() implementation
      template<typename... ints,
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type at(const ints... i) const { return Op<L,R>::apply(m_lhs, m_rhs, i...); }
      
      // operator() implementation
      template<typename... ints, 
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type operator()(const ints... i) const { return at(i...); }
      
      //template<typename... ints, 
      //         //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
      //         //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         utility::Requesting_slice<order, ints...> = 0>
      //auto operator()(const ints... i)       -> decltype(std::declval<base_type>().c_expr(i...)) 
      //{ return base_type::c_expr(i...); }
      
      //template<typename... ints, 
      //         //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
      //         //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         utility::Requesting_slice<order, ints...> = 0>
      //auto operator()(const ints... i) const -> decltype(std::declval<base_type>().c_expr(i...)) 
      //{ return base_type::c_expr(i...); }
      
      //using expression<binary_expression<L,R,Op>, traits<binary_expression<L,R,Op> > >::operator();

      // vec_at()
      /*template<class U = L,
                 metaprog::iEnable_if<utility::has_vec_at<U>::value && utility::has_vec_at<R>::value && utility::has_apply_vec<Op<L,R>,L,R>::value> = 0
      >
      value_type vec_at(const size_type i) const
      { return Op<L,R>::apply_vec(m_lhs, m_rhs, i); } */

      // size() implementation
      size_type size() const { return Op<L,R>::size(m_lhs, m_rhs); } 

      // extent() implementation
      template<int N>
      size_type extent() const { return Op<L,R>::template extent<N>(m_lhs, m_rhs); }
};

/**
 * unary expression
 **/
template<class A, template<class> class Op>
class unary_expression:
   public expression<unary_expression<A,Op>, traits<unary_expression<A,Op> > >
{
   public:
      using traits_type = traits<unary_expression<A,Op> >;
      using value_type  = Value_type<traits_type>;
      using size_type   = Size_type<traits_type>;
      static const int order = Order<Op<A> >();

   private:
      const A& m_lhs;

   public:
      // constructor
      unary_expression(const A& a_lhs): m_lhs(a_lhs) { };

      // at() implementation
      template<typename... ints,
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type at(const ints... i) const { return Op<A>::apply(m_lhs,i...); }
      
      // operator() implementation
      template<typename... ints, 
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type operator()(const ints... i) const { return at(i...); }
      
      // vec_at() implementation
      /*template<class U = A,
                 metaprog::iEnable_if<utility::has_vec_at<U>::value && utility::has_apply_vec<Op<A>,A>::value > = 0
      >
      value_type vec_at(const size_type i) const
      { return Op<A>::apply_vec(m_lhs, i); } */
      
      // size() implementation
      size_type size() const { return Op<A>::size(m_lhs); }
      
      // extent implementation
      template<int N>
      size_type extent() const { return Op<A>::template extent<N>(m_lhs); }
};

// IAN: BELOW IS NOT SAFE AND GOOD I THINK
template<class A>
struct assignable_to_scalar: A
{
   template<class U = A, metaprog::iEnable_if<U::order==0> = 0> 
   operator Value_type<A>() { return this->at(); }
};
// IAN: NON-SAFE END... REST IS AWESOME

/**
 * operators for expressions
 *
 * there are no comments...
 * it was hard to write, so it should be hard to read...
 *
 * hope I remember what I was doing a year from now :)
 **/

/**
 * default binary operators ( elementwise operation! )
 **/
#define LIBMDA_CREATE_DEFAULT_BINARY_OPERATOR(NAME,OP) \
template<class L, class R> \
struct NAME; \
 \
template<class L, class R> \
struct NAME \
{ \
   static const int order = L::order; \
   \
   template<typename... ints> \
   static Value_type<L> apply(const L& a_lhs, const R& a_rhs, const ints... i) \
   { return a_lhs.at(i...) OP a_rhs.at(i...); } \
   \
   template<class U = L, metaprog::iEnable_if<utility::has_vec_at<U>::value && utility::has_vec_at<R>::value> = 0> \
   static Value_type<L> \
   apply_vec(const L& a_lhs, const R& a_rhs, const Size_type<L> i) \
   { return a_lhs.vec_at(i) OP a_rhs.vec_at(i); } \
   \
   template<int N> \
   static Size_type<L> extent(const L& a_lhs, const R& a_rhs) \
   {  return a_lhs.template extent<N>(); } \
   \
   static Size_type<L> size(const L& a_lhs, const R& a_rhs) \
   {  return a_lhs.size(); } \
};

LIBMDA_CREATE_DEFAULT_BINARY_OPERATOR(op_add,+)
LIBMDA_CREATE_DEFAULT_BINARY_OPERATOR(op_sub,-)
LIBMDA_CREATE_DEFAULT_BINARY_OPERATOR(op_mult,*)
LIBMDA_CREATE_DEFAULT_BINARY_OPERATOR(op_div,/)
#undef LIBMDA_CREATE_DEFUALT_BINARY_OPERATOR

/**
 * default unary operators
 **/
#define LIBMDA_CREATE_DEFAULT_UNARY_OPERATOR(NAME,OP) \
template<class A> \
struct NAME \
{ \
   static const int order = A::order; \
   \
   template<typename... ints> \
   static Value_type<A> apply(const A& a_lhs, const ints... i) { return OP a_lhs.at(i...); } \
   \
   template<int N> \
   static Size_type<A> extent(const A& a_lhs) {  return a_lhs.template extent<N>(); } \
   \
   static Size_type<A> size(const A& a_lhs) {  return a_lhs.size(); } \
}; 

LIBMDA_CREATE_DEFAULT_UNARY_OPERATOR(op_unary_plus,+)
LIBMDA_CREATE_DEFAULT_UNARY_OPERATOR(op_unary_minus,-)
#undef LIBMDA_CREATE_DEFAULT_UNARY_OPERATOR

/**
 * default unary functions
 **/
#define LIBMDA_CREATE_DEFAULT_UNARY_FUNCTION(NAME,FUNC) \
template<class A> \
struct NAME \
{ \
   static const int order = A::order; \
   \
   template<typename... ints> \
   static Value_type<A> apply(const A& a_lhs, const ints... i) \
   { return FUNC(a_lhs.at(i...)); } \
   \
   template<int N> \
   static Size_type<A> extent(const A& a_lhs) \
   {  return a_lhs.template extent<N>(); } \
   \
   static Size_type<A> size(const A& a_lhs) \
   {  return a_lhs.size(); } \
}; 

LIBMDA_CREATE_DEFAULT_UNARY_FUNCTION(op_cos,cos)
LIBMDA_CREATE_DEFAULT_UNARY_FUNCTION(op_sin,sin)
#undef LIBMDA_CREATE_DEFAULT_UNARY_FUNCTION

/**
 * default scalar operators
 **/
#define LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR(NAME,OP) \
template<class L, class R> \
struct NAME; \
 \
template<class L> \
struct NAME<L, Value_type<L> > \
{ \
   static const int order = L::order; \
   \
   template<typename... ints> \
   static Value_type<L> apply(const L& a_lhs, const Value_type<L>& a_rhs, ints... i) \
   { return a_lhs.at(i...) OP a_rhs; } \
   \
   template<int N> \
   static Size_type<L> extent(const L& a_lhs, const Value_type<L>& a_rhs) \
   { return a_lhs.template extent<N>(); } \
   \
   static Size_type<L> size(const L& a_lhs, const Value_type<L>& a_rhs) \
   {  return a_lhs.size(); } \
}; \
 \
template<class R> \
struct NAME<Value_type<R>, R> \
{ \
   static const int order = R::order; \
   \
   template<typename... ints> \
   static Value_type<R> apply(const Value_type<R>& a_lhs, const R& a_rhs, ints... i) \
   { return a_lhs OP a_rhs.at(i...); } \
   \
   template<int N> \
   static Size_type<R> extent(const Value_type<R>& a_lhs, const R& a_rhs) \
   { return a_rhs.template extent<N>(); } \
   \
   static Size_type<R> size(const Value_type<R>& a_lhs, const R& a_rhs) \
   {  return a_rhs.size(); } \
}; 


LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR(op_scal_add,+)
LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR(op_scal_sub,-)
LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR(op_scal_mult,*)
LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR(op_scal_div,/)
#undef LIBMDA_CREATE_DEFAULT_SCALAR_BINARY_OPERATOR

/**
 * default scalar equal operators (applies scalar operation to each element!)
 **/
#define LIBMDA_CREATE_SCALAR_EQUAL_OPER(NAME,OP) \
struct NAME \
{ \
   template<typename V, typename... ints> \
   static void apply(V& v, const Value_type<V>& u, const ints... i) \
   { v.at(i...) OP u; } \
};

LIBMDA_CREATE_SCALAR_EQUAL_OPER(op_equal_scal,=)
LIBMDA_CREATE_SCALAR_EQUAL_OPER(op_plus_equal_scal,+=)
LIBMDA_CREATE_SCALAR_EQUAL_OPER(op_sub_equal_scal,-=)
LIBMDA_CREATE_SCALAR_EQUAL_OPER(op_mult_equal_scal,*=)
LIBMDA_CREATE_SCALAR_EQUAL_OPER(op_div_equal_scal,/=)
#undef LIBMDA_CREATE_SCALAR_EQUAL_OPER


/**
 * traits for expression structs
 **/
template<class L, class R, template<class, class> class Op> //// FIX!!!
struct traits<expr::binary_expression<L,R,Op> >
{
   using value_type = Value_type<take_out_types<L,R> >;
   using size_type  = Size_type<take_out_types<L,R> >;
   using type       = expr::binary_expression<L,R,Op>;
   static const int order = Op<L,R>::order;
};

template<class A, template<class> class Op>
struct traits<expr::unary_expression<A,Op> >
{
   using value_type = Value_type<A>;
   using size_type  = Size_type<A>;
   using type       = expr::unary_expression<A,Op>;
   static const int order = Op<A>::order;
};

} // namesspace expr

// binary expression inherits operators from one of the two types (they must have same operators anyways!)
template<class L, class R, template<class, class> class Op>
struct operator_traits<expr::binary_expression<L,R,Op> > : 
         operator_traits< Type<expr::take_out_types<L,R> > >
{ };
// unary expression inherits operators from type
template<class A, template<class> class Op>
struct operator_traits<expr::unary_expression<A,Op> > : operator_traits<Type<A> >
{ };

// default operators traits... use default expr operators
struct default_operator_traits
{
   template<class L, class R>
   using oper_add = expr::op_add<L,R>;
   template<class L, class R>
   using oper_sub = expr::op_sub<L,R>;
   template<class L, class R>
   using oper_mult = expr::op_mult<L,R>;
   template<class L, class R>
   using oper_div = expr::op_div<L,R>;
   
   template<class B>
   using oper_cos = expr::op_cos<B>;
   template<class B>
   using oper_sin = expr::op_sin<B>;

   template<class L, class R>
   using oper_scal_add = expr::op_scal_add<L,R>;
   template<class L, class R>
   using oper_scal_sub = expr::op_scal_sub<L,R>;
   template<class L, class R>
   using oper_scal_mult = expr::op_scal_mult<L,R>;
   template<class L, class R>
   using oper_scal_div = expr::op_scal_div<L,R>;

   template<class B>
   using oper_unary_plus = expr::op_unary_plus<B>;
   template<class B>
   using oper_unary_minus = expr::op_unary_minus<B>;
};

// default operator traits is to inherit from the collected default operators
template<class A> struct operator_traits: default_operator_traits { };

// mixin to assign from scalar
template<class A>
struct scalar_assign: public A
{
   using base_type  = A;
   using type       = Type<A>;
   using value_type = Value_type<A>;
   
   using A::operator=;
   using A::operator+=;
   using A::operator-=;
   using A::operator*=;
   using A::operator/=;

   type& operator=(const value_type& v)
   {
      utility::for_loop_expand<expr::op_equal_scal>::apply((*this),v);
      return this->self();
   }
   type& operator+=(const value_type& v)
   {
      utility::for_loop_expand<expr::op_plus_equal_scal>::apply((*this),v);
      return this->self();
   }
   type& operator-=(const value_type& v)
   {
      utility::for_loop_expand<expr::op_sub_equal_scal>::apply((*this),v);
      return this->self();
   }
   type& operator*=(const value_type& v)
   {
      utility::for_loop_expand<expr::op_mult_equal_scal>::apply((*this),v);
      return this->self();
   }
   type& operator/=(const value_type& v)
   {
      utility::for_loop_expand<expr::op_div_equal_scal>::apply((*this),v);
      return this->self();
   }
};

} // namespace libmda

#endif /* LIBMDA_EXPR_EXPRESSION_H */
