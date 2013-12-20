#ifndef LIBMDA_EXPR_INTERFACE_H
#define LIBMDA_EXPR_INTERFACE_H

#include "char_expression.h"
#include "expression.h"
#include "../utility/dimensions_check.h"
#include "../metaprog/std_wrappers.h"
#include "../basic_using.h"
#include "../utility/Requesting.h"

namespace libmda
{

template<class A, class trait = traits<A>, class dims_check = utility::dimensions_nocheck>
struct expression_interface:
   public libmda::scalar_assign<
          libmda::IMDAElemAssignMult<dims_check,
          libmda::IMDAElemAssign<dims_check,
          //libmda::char_expr::char_expression_interface<
          libmda::operators::expression_scalar_binary_operators<operator_traits<A>::template oper_scal_add, operator_traits<A>::template oper_scal_sub, operator_traits<A>::template oper_scal_mult, operator_traits<A>::template oper_scal_div,
          libmda::operators::expression_trigonometri_functions<operator_traits<A>::template oper_cos, operator_traits<A>::template oper_sin,
          libmda::operators::expression_unary_operators<operator_traits<A>::template oper_unary_plus, operator_traits<A>::template oper_unary_minus,
          libmda::operators::expression_binary_operators<operator_traits<A>::template oper_add, operator_traits<A>::template oper_sub, operator_traits<A>::template oper_mult, operator_traits<A>::template oper_div,
          libmda::expr::expression_base<
          libmda::char_expr::char_expression_interface<
          libmda::IMDAVecAccessComb<
          libmda::IMDAVecAccess<Ref_access(),
          libmda::IMDAAccessComb<
          libmda::IMDAAccess<Ref_access(),
          libmda::IMDADim<
          libmda::IMDASelf<
          A, trait
          > > > > > > > > > > > > > > >,
          IMDABase
{
   typedef libmda::scalar_assign<
           libmda::IMDAElemAssignMult<dims_check,
           libmda::IMDAElemAssign<dims_check,
           //libmda::char_expr::char_expression_interface<
           libmda::operators::expression_scalar_binary_operators<operator_traits<A>::template oper_scal_add, operator_traits<A>::template oper_scal_sub, operator_traits<A>::template oper_scal_mult, operator_traits<A>::template oper_scal_div,
           libmda::operators::expression_trigonometri_functions<operator_traits<A>::template oper_cos, operator_traits<A>::template oper_sin,
           libmda::operators::expression_unary_operators<operator_traits<A>::template oper_unary_plus, operator_traits<A>::template oper_unary_minus,
           libmda::operators::expression_binary_operators<operator_traits<A>::template oper_add, operator_traits<A>::template oper_sub, operator_traits<A>::template oper_mult, operator_traits<A>::template oper_div,
           libmda::expr::expression_base<
           libmda::char_expr::char_expression_interface<
           libmda::IMDAVecAccessComb<
           libmda::IMDAVecAccess<Ref_access(),
           libmda::IMDAAccessComb<
           libmda::IMDAAccess<Ref_access(),
           libmda::IMDADim<
           libmda::IMDASelf<
           A, trait
           > > > > > > > > > > > > > > > imda_interface;

   using imda_interface::operator=;
   using imda_interface::operator+=;
   using imda_interface::operator-=;
   using imda_interface::operator*=;
   using imda_interface::operator/=;

   /* non-const version */
   template<typename... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<trait>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<trait>(),cints...> = 0>
   libmda::char_expr::mda_char_expression<Type<imda_interface>, cints...>
   operator()(const cints... ci)       { return imda_interface::c_expr(ci...); }
   
   /* const version */
   template<typename... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<trait>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<trait>(),cints...> = 0>
   libmda::char_expr::mda_char_expression<const Type<imda_interface>, cints...>
   operator()(const cints... ci) const { return imda_interface::c_expr(ci...); }
};

} // namespace libmda

#endif /* LIBMDA_EXPR_INTERFACE_H */
