#ifndef LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED
#define LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED

//#include<iostream>
//#include<iomanip>
//#include<chrono>
//#include<thread>

#include <cmath>

//#include "phi_func.h"
#include "../float_eq.h"
#include "../signum.h"

#define ACCURACY 2

namespace libmda
{
namespace numeric
{
namespace optim
{
namespace detail
{

/*! bisection
 *
 */
template<class PHI>
typename PHI::step_t bisection
   ( const PHI& phi
   , const typename PHI::step_t& alpha_i
   , const typename PHI::step_t& alpha_im1
   )
{
   using step_t = typename PHI::step_t;
   return (alpha_i + alpha_im1) / static_cast<step_t>(2.0);
}

/*! do cubic interpolation
 *
 */
template<class PHI>
typename PHI::step_t cubic_interpolation
   ( const PHI& phi
   , const typename PHI::step_t& alpha_i
   , const typename PHI::step_t& alpha_im1
   )
{
   using step_t = typename PHI::step_t;

   auto phi_i = phi(alpha_i);
   auto phi_deriv_i = phi.first_derivative(alpha_i);
   auto phi_im1 = phi(alpha_im1);
   auto phi_deriv_im1 = phi.first_derivative(alpha_im1);

   auto d1 = phi_deriv_im1 + phi_deriv_i - static_cast<step_t>(3.0)*(phi_im1 - phi_i)/(alpha_im1 - alpha_i);
   auto d2 = libmda::numeric::signum(alpha_i - alpha_im1)*std::sqrt(d1*d1 - phi_deriv_im1*phi_deriv_i);

   auto alpha_new = alpha_i - (alpha_i - alpha_im1)*(phi_deriv_i + d2 - d1)/(phi_deriv_i - phi_deriv_im1 + static_cast<step_t>(2.0)*d2);
   
   if( //libmda::numeric::float_neg(alpha_new)
  /*||*/ libmda::numeric::float_eq(alpha_new, alpha_i  , 10000)
    ||   libmda::numeric::float_eq(alpha_new, alpha_im1, 10000)
     )
   {
      alpha_new = bisection(phi, alpha_i, alpha_im1);
   }

   volatile bool test = alpha_new != alpha_new;
   if(test || libmda::numeric::float_neg(alpha_new))
   {
      std::cout << " WARNING !!!! " << std::endl;
      
      std::cout << " alpha_i       : " << alpha_i << std::endl;
      std::cout << " alpha_im1     : " << alpha_im1 << std::endl;

      std::cout << " phi_i         : " << phi_i << std::endl;
      std::cout << " phi_deriv_i   : " << phi_deriv_i << std::endl;
      std::cout << " phi_im1       : " << phi_im1 << std::endl;
      std::cout << " phi_deriv_im1 : " << phi_deriv_im1 << std::endl;

      std::cout << " d1            : " << d1 << std::endl;
      std::cout << " d2            : " << d2 << std::endl;
   }

   return alpha_new;
}

/*! check for a given alpha that it fulfills the strong wolfe conditions
 *
 */
template<class PHI>
bool strong_wolfe_check
   ( PHI& phi
   , typename PHI::step_t c_1
   , typename PHI::step_t c_2
   , typename PHI::step_t alpha
   )
{
   bool decr_cond = libmda::numeric::float_leq(phi(alpha), (phi(0.0) + c_1*alpha*phi.first_derivative(0.0)), ACCURACY + 2);
   bool curv_cond = libmda::numeric::float_leq(std::fabs(phi.first_derivative(alpha)), c_2*std::fabs(phi.first_derivative(0.0)), ACCURACY + 2);

   return decr_cond && curv_cond;
}

/*! zoom in on an alpha between two end points
 *
 */
template<class PHI>
typename PHI::step_t zoom
   ( const PHI& phi
   , typename PHI::step_t a_low
   , typename PHI::step_t a_high
   , const typename PHI::value_t& phi_deriv_c2
   , const typename PHI::value_t& c_1
   , const typename PHI::value_t& phi_0
   , const typename PHI::value_t& phi_deriv_0
   )
{
   typename PHI::step_t a_j = static_cast<typename PHI::step_t>(0.0);

   //std::cout << " zoom begin :  a_low = " << a_low << "    a_high = " << a_high << std::endl;

   while(true)
   {
      if(libmda::numeric::float_eq(a_high, a_low, ACCURACY)) // check if a_high == a_low ( == a_j ) 
      {
         std::cout << " BREAK " << std::endl;
         break; // we do not satisfy the strong wolfe conditions 
                // (but it is the best we can do given the range)
      }
      
      //a_j = bisection(phi, a_high, a_low);   // bisection (could also do some interpolation)
      //a_j = detail::cubic_interpolation(phi, a_high, a_low);
      a_j = detail::cubic_interpolation(phi, a_low, a_high);
                                   
      auto phi_j     = phi(a_j); 
      auto phi_low   = phi(a_low);
      auto decr_cond = phi_0 + c_1*a_j*phi_deriv_0;
      
      if( libmda::numeric::float_gt (phi_j, decr_cond, ACCURACY) 
       || libmda::numeric::float_geq(phi_j, phi_low  , ACCURACY) // 
        ) 
      {
         a_high = a_j;
      }
      else
      {
         auto phi_deriv_j = phi.first_derivative(a_j);
         
         if( libmda::numeric::float_leq(std::fabs(phi_deriv_j), phi_deriv_c2, ACCURACY) )
         {
            break; // break while and return a_j
         }
         
         //if( libmda::numeric::float_pos(phi_deriv_j*(a_high - a_low)) )
         //if( libmda::numeric::float_numgeq_zero(phi_deriv_j*(a_high - a_low), phi_0, ACCURACY) )
         //if( libmda::numeric::float_pos(phi_deriv_j*(a_high - a_j)) )
         if( libmda::numeric::float_numgeq_zero(phi_deriv_j*(a_high - a_j), phi_0, ACCURACY) )
         {
            a_high = a_low;
         }

         a_low = a_j;
      }
   }

   //std::cout << " zoom end   :  a_low = " << a_low << "    a_high = " << a_high << "    a_j = " << a_j << std::endl;
   
   return a_j;
}

} /* namespace detail */

/*! wolfe line search algorithm
 *
 */
template<class PHI>
typename PHI::step_t wolfe_line_search
   ( const PHI& phi
   , typename PHI::step_t alpha_init
   , typename PHI::step_t alpha_max
   , typename PHI::step_t alpha_resolution = 0.1
   , typename PHI::step_t c_1 = 1e-4
   , typename PHI::step_t c_2 = 0.1
   )
{
   using step_t = typename PHI::step_t;

   auto alpha_nstep = (alpha_max - alpha_init)/alpha_resolution;
   auto alpha_old = alpha_init;
   auto alpha_new = alpha_old + alpha_resolution;
   
   auto phi_0        = phi(0.0);
   auto phi_deriv_0  = phi.first_derivative(0.0);
   auto phi_deriv_c2 = -phi_deriv_0*c_2;

   auto phi_old = phi_0;
   
   // start looping
   for(int i = 0; i < alpha_nstep; ++i)
   {
      auto phi_new   = phi(alpha_new); // evaluate phi(alpha_i)
      auto decr_cond = phi_0 + c_1*alpha_new*phi_deriv_0; // sufficient decrease condition

      if(  libmda::numeric::float_gt(phi_new, decr_cond, ACCURACY) 
       || (libmda::numeric::float_geq(phi_new, phi_old, ACCURACY) && i > 0) 
        )  
      {
         // zoom...
         alpha_new = detail::zoom(phi, alpha_old, alpha_new, phi_deriv_c2, c_1, phi_0, phi_deriv_0);
         break; // break while and return alpha_new
      }
      
      auto phi_deriv_new = phi.first_derivative(alpha_new); // evaluate phi'(alpha_i)
      if( libmda::numeric::float_leq(std::fabs(phi_deriv_new), phi_deriv_c2, ACCURACY) )
      {
         break; // break while and return alpha_new
      }

      //if( libmda::numeric::float_geq(phi_deriv_new,0.0,ACCURACY) )
      //if( libmda::numeric::float_pos(phi_deriv_new) )
      if( libmda::numeric::float_numgeq_zero(phi_deriv_new, phi_0, ACCURACY) )
      {
         // zoom (order of alpha_new and alpha_old ??...)
         alpha_new = detail::zoom(phi, alpha_new, alpha_old, phi_deriv_c2, c_1, phi_0, phi_deriv_0);
         break; // break while and return alpha_new
      }

      alpha_old = alpha_new;
      alpha_new += alpha_resolution;
      
      phi_old = phi_new;
   }
   
   // check new alpha
   bool hard_check = true;
   if(hard_check && !detail::strong_wolfe_check(phi, c_1, c_2, alpha_new))
   {
      std::cout << " WARNING ALPHA DOES NOT SATISFY STRONG WOLFE CHECK! " << std::endl;
      std::cout << alpha_new << std::endl;
      exit(1);
   }

   return detail::strong_wolfe_check(phi, c_1, c_2, alpha_new) ? alpha_new : static_cast<step_t>(0.0);
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#undef ACCURACY

#endif /* LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED */
