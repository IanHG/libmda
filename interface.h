#ifndef LIBMDA_INTERFACE_H
#define LIBMDA_INTERFACE_H

template<class A> struct traits;

namespace libmda
{
    //template<class A> struct traits;

    struct default_operator_traits;
    template<class A> struct operator_traits;

    struct IMDABase;
    template<class A, class trait> struct IMDASelf;
    template<class A> struct IMDADim;
    template<bool RefAccess, class A> struct IMDAAccess;
    //template<class A> struct IMDAAccessComb: A { };
    template<class A> struct IMDAAccessComb;
    template<class dims_check, class A> struct IMDAElemAssign;
    template<class dims_check, class A> struct IMDAElemAssignMult;
} // namespace libmda

#include "IMDA.h"

namespace libmda
{
   template<class A> struct scalar_assign;
   
namespace utility // namespace utility
{
   struct dimensions_check;
   struct dimensions_nocheck;
} // namespace utility

    template<class A, class trait>
    struct IMDAInterface:
       scalar_assign<
       IMDAElemAssignMult<utility::dimensions_nocheck,
       IMDAElemAssign    <utility::dimensions_nocheck,
       IMDAAccessComb<
       IMDAAccess<Ref_access(),
       IMDADim<
       IMDASelf< 
       A, trait
       > > > > > > >,
       IMDABase
    {
       using scalar_assign<
             IMDAElemAssignMult<utility::dimensions_nocheck,
             IMDAElemAssign    <utility::dimensions_nocheck,
             IMDAAccessComb<
             IMDAAccess<Ref_access(),
             IMDADim<
             IMDASelf< 
             A, trait
             > > > > > > >::operator=;
    };

} // namespace libmda

#include "operators/expression_binary_operators.h"
#include "utility/dimensions_check.h"

namespace libmda
{
namespace expr
{
    template<class A> struct expression_base: A { };
    template<class L, class R, template<class,class> class Op> class binary_expression;
    template<class A, template<class> class Op> class unary_expression;
    template<class A> struct assignable_to_scalar;

    
    // Move iexpression in here (or outside expr) - requires update it

} // namespace expr

} // namespace libmda

#include "expr/expression.h"
#include "ostream_output.h"



#endif /* LIBMDA_INTERFACE_H */




//////// TO DO LIST ////////

// Make chain of collectors & use these in included files!!! 
// Issue when multiple optional side by side or must choose!
// Split into files for each
// Upgrade operator= everywhere!!!
// Consider what to expose at what level!
