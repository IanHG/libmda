#ifndef HAGER_ZHANG_LINE_SEARCH_H_INCLUDED
#define HAGER_ZHANG_LINE_SEARCH_H_INCLUDED

/**
 * Implements line search algorithm as explained in:
 *    A NEW CONJUGATE GRADIENT METHOD WITH
 *    GUARANTEED DESCENT AND AN EFFICIENT LINE SEARCH
 *    
 *    WILLIAM  W.  HAGER AND HONGCHAO  ZHANG
 *
 *    SIAM J. OPTIM.  Vol. 16, No. 1, pp. 170–192
 *
 *    DOI: 10.1137/030601880
 *
 **/

#include <limits>

#include "../../util/multiple_return.h"
#include "../float_eq.h"

namespace libmda
{
namespace numeric
{
namespace optim
{
namespace detail
{

/*! Update interval.
 * 
 * @param phi
 * @param a
 * @param b
 * @param c
 *
 * @return        Returns updated interval.
 */
template<class PHI>
libmda::util::return_type<typename PHI::step_t, typename PHI::step_t> update
   ( const PHI& phi
   , typename PHI::step_t a
   , typename PHI::step_t b
   , typename PHI::step_t c
   )
{
   assert(libmda::numeric::float_leq(a, b));
   auto theta = static_cast<typename PHI::step_t>(0.5); // \theta \in (0,1)
   auto eps = std::numeric_limits<typename PHI::step_t>::epsilon() * 1e2;
   // U0
   if(libmda::numeric::float_lt(c, a) || libmda::numeric::float_gt(c, b))
   {
      return libmda::util::ret(a, b);
   }
   // U1
   auto phi_c_deriv = phi.first_derivative(c);
   if( libmda::numeric::float_geq(phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) )
   {
      return libmda::util::ret(a, c);
   }
   // U2
   auto phi_0 = phi(0);
   auto phi_c = phi(c);
   if( libmda::numeric::float_lt (phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) 
    && libmda::numeric::float_leq(phi_c, phi_0 + eps)
     )
   {
      return libmda::util::ret(c, b);
   }
   // U3
   if( libmda::numeric::float_lt(phi_c_deriv, static_cast<typename PHI::step_t>(0.0)
    && libmda::numeric::float_gt(phi_c, phi_0 + eps)
     )
   {
      auto a_hat = a;
      auto b_hat = c;
      while(true)
      {
         // a
         auto d = (static_cast<typename PHI::step_t>(1.0) - theta)*a_hat + theta*b_hat;
         auto phi_deriv_d = phi.first_derivative(d);
         if( libmda::numeric::float_geq(phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) )
         {
            return libmda::util::ret(a_hat, d);
         }
         // b
         if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) 
          && libmda::numeric::float_leq(phi_d, phi_0 + eps) 
           )
         {
            a_hat = d;
         }
         // c
         else if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) 
               && libmda::numeric::float_gt(phi_d, phi_0 + eps) 
                )
         {
            b_hat = d;
         }
         else
         {
            // should not get here ?? :O
            assert(false);
         }
     }
   }
   
   // should not get here ?? :O
   assert(false);
}

/*! Double secant step.
 *
 * @param phi
 * @param a
 * @param b
 *
 * @return 
 */
template<class PHI>
libmda::util::return_type<typename PHI::step_t, typename PHI::step_t> double_secant_step
   ( const PHI& phi
   , typename PHI::step_t a
   , typename PHI::step_t b
   )
{
   // S1
   auto phi_deriv_a = phi.first_derivative(a);
   auto phi_deriv_b = phi.first_derivative(b);
   auto c = (a*phi_deriv_a - b*phi_deriv_b)/(phi_deriv_a - phi_deriv_b);q
   auto aa = static_cast<typename PHI::step_t>(0.0);
   auto bb = static_cast<typename PHI::step_t>(0.0);
   libmda::util::ret(aa, bb) = update(phi, a, b, c);

   auto cc = static_cast<typename PHI::step_t>(0.0);
   // S2
   auto equal_a = false, equal_b = false;
   if( equal_b = libmda::numeric::float_eq(c, bb) )
   {
      auto phi_deriv_bb = phi.first_derivative(bb);
      cc = (b*phi_deriv_b - bb*phi_deriv_bb)/(phi_deriv_b - phi_deriv_bb);
   }
   // S3
   if( equal_a = libmda::numeric::float_eq(c, aa) )
   {
      auto phi_deriv_aa = phi.first_derivative(aa);
      cc = (a*phi_deriv_a - aa*phi_deriv_aa)/(phi_deriv_a - phi_deriv_aa);
   }
   // S4
   if(equal_a || equal_b)
   {
      libmda::util::ret(a, b) = update(aa, bb, cc);
      return libmda::util::ret(a, b);
   }
   else
   {
      return libmda::util::ret(aa, bb);
   }
}

} /* namespace detail */

/*!
 *
 */
template<class PHI>
typename PHI::step_t hager_zhang_line_search
   ( const PHI& phi
   , typename PHI::step_t alpha_init
   , typename PHI::step_t alpha_max
   , typename PHI::step_t alpha_resolution = 0.1
   , typename PHI::step_t c_1 = 1e-4
   , typename PHI::step_t c_2 = 0.1
   )
{
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#endif /* HAGER_ZHANG_LINE_SEARCH_H_INCLUDED */
