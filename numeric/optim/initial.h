#ifndef LIBMDA_NUMERIC_OPTIM_INITIAL_H_INCLUDED
#define LIBMDA_NUMERIC_OPTIM_INITIAL_H_INCLUDED

#include "../float_eq.h"

namespace libmda
{
namespace numeric
{
namespace optim
{

/*!
 *
 */
template
   < class PHI
   , class T
   >
typename PHI::step_t initial
   ( int k
   , const PHI& phi
   , typename PHI::step_t alpha_old
   , const T& x
   , const T& g
   , bool quadstep = false
   , typename PHI::step_t psi0 = static_cast<typename PHI::step_t>(1e-2)
   , typename PHI::step_t psi1 = static_cast<typename PHI::step_t>(1e-1)
   , typename PHI::step_t psi2 = static_cast<typename PHI::step_t>(2.0)
   )
{
   // I0
   if(k == 0)
   {
      // a)
      if(libmda::numeric::float_neq(norm(x), static_cast<typename PHI::step_t>(0.0)))
      {
         auto max_x = max_abs_element(x);
         auto max_g = max_abs_element(g);
         auto c = psi0 * max_x / max_g;
         return c;
      }
      // b)
      auto psi0 = phi(0);  
      if(libmda::numeric::float_neq(psi0, static_cast<typename PHI::step_t>(0.0)))
      {
         auto norm_g = norm(g);
         auto c = std::abs(psi0) / (norm_g * norm_g);
         return c;
      }
      // c)
      return static_cast<typename PHI::step_t>(1.0);
   }
   // I1
   if(quadstep)
   {

   }
   else
   {
      auto c = psi2 * alpha_old;
      return c;
   }
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#endif /* LIBMDA_NUMERIC_OPTIM_INITIAL_H_INCLUDED */
