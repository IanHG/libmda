/**
************************************************************************
* 
* @file    exact_3pg_line_search.h
*
* @date    23-02-2017
*
* @author  Niels Kristian Madsen (nielskm@chem.au.dk)
*
* @brief
*     Implementation of 3-PG line search described in
*     [Espig: Variational Calculus](https://link.springer.com/article/10.1007%2Fs00211-012-0464-x)
*
* @copyright
*     Ove Christiansen, Aarhus University.
*     The code may only be used and/or copied with the written permission 
*     of the author or in accordance with the terms and conditions under 
*     which the program was supplied.  The code is provided "as is" 
*     without any expressed or implied warranty.
* 
************************************************************************
**/

#ifndef LIBMDA_EXACT_3PG_LINE_SEARCH_INCLUDED
#define LIBMDA_EXACT_3PG_LINE_SEARCH_INCLUDED


#include "../float_eq.h"
#include "../signum.h"
#include "optimize_interval.h"
#include "inc_gen/Warnings.h"

#define ACCURACY 2

namespace libmda
{
namespace numeric
{
namespace optim
{

/**
 * 3-PG line search algorithm
 *
 * @param phi           Phi function
 * @param alpha_max     Guess of max step length. Will be used unless phi'(alpha_max)*phi'(0) > 0.
 * @param slope_init    Initial slope: phi'(0).
 * @param c             C parameter for 3-PG
 * @param d             D parameter for 3-PG
 * @param eps           Threshold for terminating the line search
 * @param maxiter       Maximum iterations
 *
 * @return
 *    Optimized step size
 **/
template<class PHI>
typename PHI::step_t exact_3pg_line_search
   (  const PHI& phi
   ,  typename PHI::step_t alpha_max
   ,  typename PHI::value_t slope_init
   ,  typename PHI::step_t c = 0.6
   ,  typename PHI::step_t d = 0.6
   ,  typename PHI::step_t eps = 1.e-10
   ,  size_t maxiter = 100
   )
{
   using step_t = typename PHI::step_t;

   auto a = static_cast<step_t>(0.);
   auto b = alpha_max;
   auto p_a = slope_init;
   auto p_b = phi.first_derivative(b);

   // Find interval that satisfies p_a*p_b < 0
   detail::optimize_interval(phi, a, b, p_a, p_b, static_cast<step_t>(1.e2));

   if (  libmda::numeric::float_neg(p_b)
      )
   {
      MidasWarning("3-PG line search: Slope is negative at alpha_max.");
   }

   auto R = a;
   auto p_ba = (p_b-p_a) / (b-a);
   auto alpha = b - p_b / p_ba;
   auto alpha_old = alpha;
   auto p_alpha = phi.first_derivative(alpha);
   step_t p_alpha_a = 0.;
   step_t p_alpha_b = 0.;
   step_t q = 0.;
   step_t y = 0.;

   // Begin iteration
   size_t iter = 0;
   while (  libmda::numeric::float_gt(std::fabs(p_alpha), eps)
         && iter < maxiter
         )
   {
      // Debug
//      Mout  << " ### 3-PG iteration " << iter << " ###\n"
//            << "   # a        = " << a << "\n"
//            << "   # b        = " << b << "\n"
//            << "   # p_a      = " << p_a << "\n"
//            << "   # p_b      = " << p_b << "\n"
//            << "   # alpha    = " << alpha << "\n"
//            << "   # p_alpha  = " << p_alpha << "\n"
//            << std::flush;

      // Test if a=b
      if (  libmda::numeric::float_eq(a, b, 0)
         )
      {
         MidasWarning("3-PG line search: a=b, but algorithm not converged!");

         alpha = b;
         break;
      }
      
      // Test if p_alpha*p_b < 0
      if (  libmda::numeric::float_neg(p_alpha*p_b)
         )
      {
         R = b;
      }
     
      p_alpha_a = (p_alpha-p_a) / (alpha - a); 
      p_alpha_b = (p_alpha-p_b) / (alpha - b);
      q = ( (alpha-a)*p_alpha_b + (b-alpha)*p_alpha_a ) / (b-a);

      // Test if q == 0
      if (  libmda::numeric::float_numeq_zero(q, 1.)
         )
      {
         y = static_cast<step_t>(0.5)*(R+alpha);
      }
      else
      {
         y = alpha - p_alpha / q;
      }

      if (  !libmda::numeric::float_neg((y-alpha)*(y-R))
         || (  libmda::numeric::float_gt(std::fabs(y-R), c*std::fabs(alpha-R))
            && libmda::numeric::float_gt(std::fabs(p_alpha), d*std::fabs(p_b))
            )
         )
      {
         y = static_cast<step_t>(0.5)*(R+alpha);
      }

      // Debug
//      Mout  << "   # R           = " << R << "\n"
//            << "   # p_alpha_a   = " << p_alpha_a << "\n"
//            << "   # p_alpha_b   = " << p_alpha_b << "\n"
//            << "   # q           = " << q << "\n"
//            << "   # y           = " << y << "\n"
//            << std::endl;


      // Set up for next iteration
      a = b;
      p_a = p_b;
      b = alpha;
      p_b = p_alpha;
      alpha_old = alpha;
      alpha = y;
      
      if (  alpha != alpha )
      {
         MidasWarning("3-PG alpha evaluates to " + std::to_string(alpha) + ". Return alpha_old with error = " + std::to_string(p_alpha) + ". q = " + std::to_string(q));
         alpha = alpha_old;
         break;
      }

      // Calculate new derivative
      p_alpha = phi.first_derivative(alpha);

      ++iter;
   }

   return alpha;
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#undef ACCURACY

#endif /* LIBMDA_EXACT_3PG_LINE_SEARCH_INCLUDED */
