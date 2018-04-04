/**
************************************************************************
* 
* @file    optimize_interval.h
*
* @date    02-03-2017
*
* @author  Niels Kristian Madsen (nielskm@chem.au.dk)
*
* @brief
*     Optimize step-size interval until we are sure that it contains a minimum.
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

#ifndef OPTIMIZE_INTERVAL_H_INCLUDED
#define OPTIMIZE_INTERVAL_H_INCLUDED


#include "../float_eq.h"
#include "../signum.h"
#include "inc_gen/Warnings.h"

#define ACCURACY 2

namespace libmda
{
namespace numeric
{
namespace optim
{
namespace detail
{

/**
 * Optimize step-size interval until slopes of phi function have opposite sign.
 *
 * @param phi              Phi function
 * @param alpha_min        Reference to smallest step size
 * @param alpha_max        Reference to largest step size
 * @param p_alpha_min      Slope of phi at alpha_min (NB: Must be pre-calculated! However, only the sign matters.)
 * @param p_alpha_max      Slope of phi at alpha_max (NB: Must be pre-calculated! However, only the sign matters.)
 * @param expansion_coef   Rate of expansion
 *
 * @return
 *    True if the interval has changed
 **/
template <class PHI>
bool optimize_interval
   (  const PHI& phi
   ,  typename PHI::step_t& alpha_min
   ,  typename PHI::step_t& alpha_max
   ,  typename PHI::value_t& p_alpha_min
   ,  typename PHI::value_t& p_alpha_max
   ,  typename PHI::step_t expansion_coef=1.e2
   )
{
   // Debug
//   Mout  << " Optimize line-search interval:\n"
//         << "   alpha_min = " << alpha_min << "\n"
//         << "   alpha_max = " << alpha_max << "\n"
//         << "   p_min     = " << p_alpha_min << "\n"
//         << "   p_max     = " << p_alpha_max << "\n"
//         << std::flush;

   using step_t = typename PHI::step_t;

   bool expanded = false;

   // Expand interval until the slopes have opposite sign
   while (  !libmda::numeric::float_neg(p_alpha_min*p_alpha_max)
         )
   {
      expanded = true;
      alpha_min = alpha_max;
      p_alpha_min = p_alpha_max;

      alpha_max = expansion_coef*alpha_max + static_cast<step_t>(1.e-16);
      p_alpha_max = phi.first_derivative(alpha_max);
   }

   // Debug
//   Mout  << "   new alpha_min = " << alpha_min << "\n"
//         << "   new alpha_max = " << alpha_max << "\n"
//         << "   p_min     = " << p_alpha_min << "\n"
//         << "   p_max     = " << p_alpha_max << "\n"
//         << std::flush;
   
   return expanded;
}

} /* namespace detail */
} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#undef ACCURACY

#endif /* OPTIMIZE_INTERVAL_H_INCLUDED */
