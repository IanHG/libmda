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

#include "optimize_interval.h"

namespace libmda
{
namespace numeric
{
namespace optim
{
namespace detail
{


/*!
 *
 */
template<class PHI>
libmda::util::return_type<typename PHI::step_t, typename PHI::step_t> bracket
   ( const PHI& phi
   , typename PHI::step_t c
   , typename PHI::step_t epsilon
   , typename PHI::step_t theta
   , typename PHI::step_t rho = static_cast<typename PHI::step_t>(5.0)
   )
{
   // B0
   std::vector<typename PHI::step_t> cvec;
   cvec.emplace_back(c);
   int j = 0;
   
   auto phi_0 = phi(0);
   while(true)
   {
      // B1
      auto phi_deriv_c_j = phi.first_derivative(cvec[j]);
      if( (j > 0) && libmda::numeric::float_geq(phi_deriv_c_j, static_cast<typename PHI::step_t>(0.0)) )
      {
         auto b = cvec[j];
         for(int i = cvec.size() - 2; i >= 0; --i)
         {
            auto phi_i = phi(cvec[j]);
            if( libmda::numeric::float_leq(phi_i, phi_0 + epsilon) )
            {
               auto a = cvec[i];
               std::cout << " B1 FIRST " << a << " " << b << std::endl;
               return libmda::util::ret(a, b); // return B1
            }
         }
         auto a = static_cast<typename PHI::step_t>(0.0);
         std::cout << " B1 SECOND " << a << " " << b << std::endl;
         return libmda::util::ret(a, b); // return B1
      }

      // B2
      auto phi_c_deriv = phi.first_derivative(cvec[j]);
      auto phi_c = phi(cvec[j]);
      if( libmda::numeric::float_lt(phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) // redundant
       && libmda::numeric::float_gt(phi_c, phi_0 + epsilon)                              // redundant
        )
      {
         auto a_hat = static_cast<typename PHI::step_t>(0.0);
         auto b_hat = cvec[j];
         while(true)
         {
            // a
            auto d = (static_cast<typename PHI::step_t>(1.0) - theta)*a_hat + theta*b_hat;
            auto phi_d = phi(d);
            auto phi_deriv_d = phi.first_derivative(d);
            if( libmda::numeric::float_geq(phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) )
            {
               std::cout << " B2 " << a_hat << " " << d << std::endl;
               return libmda::util::ret(a_hat, d); // return B2
            }
            // b
            if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) // redundant
             && libmda::numeric::float_leq(phi_d, phi_0 + epsilon) 
              )
            {
               a_hat = d;
            }
            // c
            else if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) // redundant
                  && libmda::numeric::float_gt(phi_d, phi_0 + epsilon)                               // redundant
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
      
      // B3
      cvec.emplace_back(rho * cvec[j]);
      ++j;
   }
}

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
   , typename PHI::step_t epsilon
   , typename PHI::step_t theta
   , typename PHI::step_t phi_0
   )
{
   assert(libmda::numeric::float_leq(a, b));
   auto phi_c_deriv = phi.first_derivative(c);
   auto phi_c = phi(c);
   // U0
   if(libmda::numeric::float_leq(c, a) || libmda::numeric::float_geq(c, b))
   {
      return libmda::util::ret(a, b);
   }
   // U1
   if( libmda::numeric::float_geq(phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) )
   {
      return libmda::util::ret(a, c);
   }
   // U2
   if( libmda::numeric::float_lt (phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) 
    && libmda::numeric::float_leq(phi_c, phi_0 + epsilon)
     )
   {
      return libmda::util::ret(c, b);
   }
   // U3
   if( libmda::numeric::float_lt(phi_c_deriv, static_cast<typename PHI::step_t>(0.0)) // redundant
    && libmda::numeric::float_gt(phi_c, phi_0 + epsilon)                              // redundant
     )
   {
      auto a_hat = a;
      auto b_hat = c;
      while(true)
      {
         // a
         auto d = (static_cast<typename PHI::step_t>(1.0) - theta)*a_hat + theta*b_hat;
         auto phi_d = phi(d);
         auto phi_deriv_d = phi.first_derivative(d);
         if( libmda::numeric::float_geq(phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) )
         {
            return libmda::util::ret(a_hat, d);
         }
         // b
         if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) // redundant
          && libmda::numeric::float_leq(phi_d, phi_0 + epsilon) 
           )
         {
            a_hat = d;
         }
         // c
         else if( libmda::numeric::float_lt (phi_deriv_d, static_cast<typename PHI::step_t>(0.0)) // redundant
               && libmda::numeric::float_gt(phi_d, phi_0 + epsilon)                               // redundant
                )
         {
            b_hat = d;
         }
         else
         {
            // should not get here ?? :O
            assert(false);
            return libmda::util::ret(a_hat, d);
         }
     }
   }
   
   // should not get here ?? :O
   assert(false);
   return libmda::util::ret(a, b);
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
   , typename PHI::step_t epsilon
   , typename PHI::step_t theta
   , typename PHI::step_t phi_0
   )
{
   // S1
   auto phi_deriv_a = phi.first_derivative(a);
   auto phi_deriv_b = phi.first_derivative(b);
   auto c = (a*phi_deriv_b - b*phi_deriv_a)/(phi_deriv_b - phi_deriv_a);
   auto aa = static_cast<typename PHI::step_t>(0.0);
   auto bb = static_cast<typename PHI::step_t>(0.0);
   libmda::util::ret(aa, bb) = update(phi, a, b, c, epsilon, theta, phi_0);

   // S2
   auto cc = static_cast<typename PHI::step_t>(0.0);
   auto equal_a = false, equal_b = false;
   if( (equal_b = libmda::numeric::float_eq(c, bb)) )
   {
      auto phi_deriv_bb = phi.first_derivative(bb);
      cc = (b*phi_deriv_bb - bb*phi_deriv_b)/(phi_deriv_bb - phi_deriv_b);
   }
   // S3
   if( (equal_a = libmda::numeric::float_eq(c, aa)) )
   {
      auto phi_deriv_aa = phi.first_derivative(aa);
      cc = (a*phi_deriv_aa - aa*phi_deriv_a)/(phi_deriv_aa - phi_deriv_a);
   }
   // S4
   if(equal_a || equal_b)
   {
      libmda::util::ret(a, b) = update(phi, aa, bb, cc, epsilon, theta, phi_0);
      return libmda::util::ret(a, b);
   }
   else
   {
      return libmda::util::ret(aa, bb);
   }
}

/*!
 *
 */
template<class PHI>
bool approximate_wolfe_conditions
   ( const PHI& phi
   , typename PHI::step_t alpha
   , typename PHI::step_t delta
   , typename PHI::step_t sigma
   , typename PHI::step_t epsilon
   , typename PHI::step_t phi_0
   )
{
   using step_t = typename PHI::step_t;
   auto phi_alpha = phi(alpha);
   //auto phi_0 = phi(0);
   auto phi_deriv_alpha = phi.first_derivative(alpha);
   auto phi_deriv_0 = phi.first_derivative(0);
   
   auto wolfe_decrease    = libmda::numeric::float_leq(phi_alpha, phi_0 + delta*alpha*phi_deriv_0);
   auto wolfe_curvature   = libmda::numeric::float_geq(phi_deriv_alpha, sigma*phi_deriv_0);
   //auto wolfe_curvature   = libmda::numeric::float_leq(std::abs(phi_deriv_alpha), -sigma*phi_deriv_0);
   auto wolfe_approximate = libmda::numeric::float_geq((static_cast<step_t>(2.0)*delta - static_cast<step_t>(1.0))*phi_deriv_0, phi_deriv_alpha)
                         && wolfe_curvature;
   auto wolfe_epsilon     = libmda::numeric::float_leq(phi_alpha, phi_0 + epsilon);
   
   //std::cout << " alpha             = " << alpha << std::endl;
   //std::cout << " wolfe_decrease    = " << std::boolalpha << wolfe_decrease << std::endl;
   //std::cout << " wolfe_curvature   = " << std::boolalpha << wolfe_curvature << std::endl;
   //std::cout << " wolfe_approximate = " << std::boolalpha << wolfe_approximate << std::endl;
   
   //     T1                                  || T2
   return (wolfe_decrease && wolfe_curvature) || (wolfe_approximate && wolfe_epsilon);
}

/*!
 *
 */
template<class PHI>
bool a_condition
   ( const PHI& phi
   , typename PHI::step_t a
   , typename PHI::step_t epsilon
   , typename PHI::step_t phi_0
   )
{
   auto phi_a = phi(a);
   auto phi_deriv_a = phi.first_derivative(a);
   std::cout << " PHI A : " << phi_a << std::endl;
   std::cout << " PHI 0 : " << phi_0 << std::endl;
   std::cout << " PHI DERIV A : " << phi_deriv_a << std::endl;
   return ( libmda::numeric::float_leq(phi_a, phi_0 + epsilon)
         && libmda::numeric::float_lt(phi_deriv_a, static_cast<typename PHI::step_t>(0.0))
          );
}

/*!
 *
 */
template<class PHI>
bool b_condition
   ( const PHI& phi
   , typename PHI::step_t b
   )
{
   auto phi_deriv_b = phi.first_derivative(b);
   return libmda::numeric::float_geq(phi_deriv_b, static_cast<typename PHI::step_t>(0.0));
}


} /* namespace detail */

/*!
 *
 */
template<class PHI>
typename PHI::step_t hager_zhang_line_search
   (  const PHI& phi
   ,  typename PHI::step_t alpha_a
   ,  typename PHI::step_t alpha_b
   ,  bool optimize_interval = false
   ,  typename PHI::value_t slope_init = -1. // Sign of phi'(alpha_a). Used in optimize_interval.
   ,  typename PHI::step_t delta = 1e-4     // (.0, .5)
   ,  typename PHI::step_t sigma = 0.1      // [\delta, 1.0)
   ,  typename PHI::step_t epsilon = 1e-6    // [.0, \inf)
   ,  typename PHI::step_t theta = 0.5      // (.0, 1.0)
   ,  typename PHI::step_t gamma = 0.66      // (.0, 1.0)
   ,  typename PHI::step_t rho = 5.0      // (.0, \inf)
   )
{
   using step_t = typename PHI::step_t;
   auto phi_0 = phi(0);

   // Make sure the interval contains an extremum point
   if (  optimize_interval )
   {
      std::cout << " =============== starting interval optimization ================= " << std::endl;
      std::cout << " alpha_a before opt = " << alpha_a << std::endl;
      std::cout << " alpha_b before opt = " << alpha_b << std::endl;

      auto p_a = slope_init;
      auto p_b = phi.first_derivative(alpha_b);

      detail::optimize_interval(phi, alpha_a, alpha_b, p_a, p_b, static_cast<step_t>(1.e2));

      std::cout << " alpha_a after opt = " << alpha_a << std::endl;
      std::cout << " alpha_b after opt = " << alpha_b << std::endl;
   }

   // bracket interval
   libmda::util::ret(alpha_a, alpha_b) = detail::bracket(phi, alpha_b, epsilon, theta, rho);

   std::cout << " alpha_a after bracket = " << alpha_a << std::endl;
   std::cout << " alpha_b after bracket = " << alpha_b << std::endl;

   //std::cout << " ALPHA_A " << alpha_a << std::endl;
   //std::cout << " ALPHA_B " << alpha_b << std::endl;
   //if(!detail::a_condition(phi, alpha_a, epsilon, phi_0))
   //{
   //   std::cout << "A CONDITION NOT SATISFIED! alpha_a = " << alpha_a << std::endl;
   //}
   //if(!detail::b_condition(phi, alpha_b))
   //{
   //   std::cout << "B CONDITION NOT SATISFIED! alpha_b = " << alpha_b << std::endl;
   //}


   while(true)
   {  
      std::cout << " =============== starting line search loop ================= " << std::endl;
      std::cout << " alpha_a = " << alpha_a << std::endl;
      std::cout << " alpha_b = " << alpha_b << std::endl;
      auto phi_a = phi(alpha_a);
      auto phi_b = phi(alpha_b);
      auto phi_deriv_a = phi.first_derivative(alpha_a);
      
      // L0
      // check wolfe conditions for end points
      if(detail::approximate_wolfe_conditions(phi, alpha_a, delta, sigma, epsilon, phi_0))
      {
         std::cout << " =============== stopping A ================= " << std::endl;
         return alpha_a;
      }
      if(detail::approximate_wolfe_conditions(phi, alpha_b, delta, sigma, epsilon, phi_0))
      {
         std::cout << " =============== stopping B ================= " << std::endl;
         return alpha_b;
      }
      // check for equality between a and b
      if(libmda::numeric::float_eq(alpha_a, alpha_b)) 
      {
         std::cout << " !!! WARNING A == B !!! " << std::endl;
         std::cout << " =============== stopping A == B ================= " << std::endl;
         return static_cast<step_t>(0.0);
      }

      // L1
      auto alpha_a_new = static_cast<step_t>(0.0);
      auto alpha_b_new = static_cast<step_t>(0.0);
      libmda::util::ret(alpha_a_new, alpha_b_new) = detail::double_secant_step(phi, alpha_a, alpha_b, epsilon, theta, phi_0);
      if(detail::approximate_wolfe_conditions(phi, alpha_a_new, delta, sigma, epsilon, phi_0))
         return alpha_a_new;
      if(detail::approximate_wolfe_conditions(phi, alpha_b_new, delta, sigma, epsilon, phi_0))
         return alpha_b_new;
      // L2
      if(libmda::numeric::float_gt(alpha_b_new - alpha_a_new, gamma*(alpha_b - alpha_a)))
      {
         auto c = (alpha_a_new + alpha_b_new)/static_cast<step_t>(2.0);
         if(detail::approximate_wolfe_conditions(phi, c, delta, sigma, epsilon, phi_0))
            return c;
         libmda::util::ret(alpha_a_new, alpha_b_new) = detail::update(phi, alpha_a_new, alpha_b_new, c, epsilon, theta, phi_0);
      }
      // L3
      alpha_a = alpha_a_new;
      alpha_b = alpha_b_new;
   }
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#endif /* HAGER_ZHANG_LINE_SEARCH_H_INCLUDED */
