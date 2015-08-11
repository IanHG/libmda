#ifndef LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED
#define LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED

//#include<iostream>
//#include<iomanip>
//#include<chrono>
//#include<thread>

//#include "phi_func.h"
#include "../float_eq.h"

#define ACCURACY 4

namespace libmda
{
namespace numeric
{
namespace optim
{

template<class PHI>
typename PHI::step_t zoom( PHI& phi
                         , typename PHI::step_t a_low
                         , typename PHI::step_t a_high
                         , typename PHI::value_t phi_deriv_c2
                         , typename PHI::value_t c_1
                         , typename PHI::value_t phi_0
                         , typename PHI::value_t phi_deriv_0
                         )
{
   //std::cout << " starting zoom: " << std::endl;
   
   decltype((a_high+a_low)/2.0) a_j;
   // these two are ineffcient... (pass as arguments to function)
   //auto phi_0        = phi(0.0);
   //auto phi_deriv_0  = phi.first_derivative(0.0);

   while(true)
   {
      a_j = (a_high + a_low) / 2.0;   // bisection (could also do some interpolation)
      
      //std::cout << a_j << std::endl;
      if(libmda::numeric::float_eq(a_high,a_low,ACCURACY)) // check if a_high == a_low ( == a_j ) 
      {
         //std::cout << " BREAKING ! " << std::endl;
         //exit(84);
         break; // we do not satisfy the strong wolfe conditions 
                // (but it is the best we can do given the range)
      }
                                   

      //std::cout << " zoom loop: a_j = " << a_j << "\t" 
      //          << " a_high = " << a_high << "\t"
      //          << " a_low  = " << a_low  << std::endl;

      //auto phi_deriv_j_out = phi.first_derivative(a_j);
      //std::cout << " |phi'(a_j)|    = " << fabs(phi_deriv_j_out) << std::endl;
      //std::cout << " -c_2*phi'(0) = " << phi_deriv_c2 << std::endl;
      //std::cout << " leq: " << libmda::numeric::float_leq(fabs(phi_deriv_j_out),phi_deriv_c2,2) << std::endl;
      //std::this_thread::sleep_for(std::chrono::seconds(1));
      
      //std::cout << " calculating phi_j " << std::endl;
      auto phi_j     = phi(a_j); 
      auto phi_low   = phi(a_low);
      auto decr_cond = phi_0 + c_1*a_j*phi_deriv_0;
      
      //if( libmda::numeric::float_gt(phi_j,decr_cond,2) || libmda::numeric::float_geq(phi_j, phi_low,2) )
      if( libmda::numeric::float_gt(phi_j, decr_cond, ACCURACY) 
       || libmda::numeric::float_gt(phi_j, phi_low  , ACCURACY) ) // ian: I have made last check 'greater than' instead of 'greater than or equal' because of general float behavior
      {
         //std::cout << " condition1 : " << libmda::numeric::float_gt(phi_j,decr_cond,2) << std::endl;

         //std::cout << " phi_j   = " << std::setprecision(20) << phi_j << std::endl;
         //std::cout << " phi_low = " << std::setprecision(20) << phi_low << std::endl;
         //std::cout << " condition2 : " << libmda::numeric::float_geq(phi_j, phi_low,2) << std::endl;
         
         //auto phi_deriv_j = phi.first_derivative(a_j);
         //std::cout << " |phi'(a_j)|    = " << fabs(phi_deriv_j) << std::endl;
         //std::cout << " -c_2*phi'(0) = " << phi_deriv_c2 << std::endl;
         //std::cout << " leq: " << libmda::numeric::float_leq(fabs(phi_deriv_j),phi_deriv_c2,2) << std::endl;

         a_high = a_j;
      }
      else
      {
         auto phi_deriv_j = phi.first_derivative(a_j);
         //std::cout << " |phi'(a_j)|    = " << fabs(phi_deriv_j) << std::endl;
         //std::cout << " -c_2*phi'(0) = " << phi_deriv_c2 << std::endl;
         //std::cout << " leq: " << libmda::numeric::float_leq(fabs(phi_deriv_j),phi_deriv_c2,2) << std::endl;
         if( libmda::numeric::float_leq(fabs(phi_deriv_j),phi_deriv_c2,ACCURACY) )
            break; // break while and return a_j
         //if( libmda::numeric::float_geq(phi_deriv_j*(a_high - a_low),0.0,ACCURACY) )
         if( libmda::numeric::float_pos(phi_deriv_j*(a_high - a_low)) )
            a_high = a_low;
         a_low = a_j;
      }
   }

   //std::cout << " and here ! " << std::endl;
   
   return a_j;
}

template<class PHI>
typename PHI::step_t wolfe_line_search( PHI& phi
                                      , typename PHI::step_t alpha_max
                                      , typename PHI::step_t c_1 = 1e-4
                                      , typename PHI::step_t c_2 = 0.1
                                      )
{
   auto alpha_old = 0.0;
   auto alpha_new = (alpha_old+alpha_max)/2.0;
   
   auto phi_0        = phi(0.0);
   auto phi_deriv_0  = phi.first_derivative(0.0);
   auto phi_deriv_c2 = -phi_deriv_0*c_2;

   //assert(libmda::numeric::float_lt(phi_deriv_0,0.0));

   auto phi_old = phi_0;

   unsigned i = 1; // start counting from 1
   while(true)
   {
      //std::cout << " starting wolfe loop " << i << std::endl;
      auto phi_new   = phi(alpha_new); // evaluate phi(alpha_i)
      auto decr_cond = phi_0 + c_1*alpha_new*phi_deriv_0; // sufficient decrease condition
      
      //std::cout << " here " << std::endl;
      //std::cout << " c_1         = " << c_1 << std::endl;
      //std::cout << " phi_0       = " << phi_0 << std::endl;
      //std::cout << " phi_deriv_0 = " << phi_deriv_0 << std::endl;
      //std::cout << " alpha_new   = " << alpha_new << std::endl;
      //std::cout << " phi_new     = " << phi_new << std::endl;
      //std::cout << " decr_cond   = " << decr_cond << std::endl;
      //std::cout << " end here " << std::endl;

      if(  libmda::numeric::float_gt(phi_new,decr_cond,ACCURACY) 
       || (libmda::numeric::float_geq(phi_new,phi_old,ACCURACY) && i > 1) )  
      {
         // zoom...
         //std::cout << " starting zoom loop from 1 " << std::endl;
         alpha_new = zoom(phi, alpha_old, alpha_new, phi_deriv_c2, c_1, phi_0, phi_deriv_0);
         break; // break while and return alpha_new
      }
      
      auto phi_deriv_new = phi.first_derivative(alpha_new); // evaluate phi'(alpha_i)
      if( libmda::numeric::float_leq(fabs(phi_deriv_new),phi_deriv_c2,ACCURACY) )
         break; // break while and return alpha_new

      //if( libmda::numeric::float_geq(phi_deriv_new,0.0,ACCURACY) )
      if( libmda::numeric::float_pos(phi_deriv_new) )
      {
         // zoom (order of alpha_new and alpha_old ??...)
         //std::cout << " starting zoom loop from 2 " << std::endl;
         alpha_new = zoom(phi, alpha_new, alpha_old, phi_deriv_c2, c_1, phi_0, phi_deriv_0);
         break; // break while and return alpha_new
      }

      alpha_old = alpha_new;
      alpha_new = (alpha_new+alpha_max)/2.0;
      
      //std::cout << " alpha_old = " << alpha_old << "\t alpha_new = " << alpha_new << std::endl;

      phi_old = phi_new;
      
      ++i; // incr counter
   }

   return alpha_new;
}

template<class PHI>
bool strong_wolfe_check( PHI& phi
                       , typename PHI::step_t c_1
                       , typename PHI::step_t c_2
                       , typename PHI::step_t alpha
                       )
{
   bool decr_cond = libmda::numeric::float_leq(phi(alpha),(phi(0.0) + c_1*alpha*phi.first_derivative(0.0)));
   bool curv_cond = libmda::numeric::float_leq(fabs(phi.first_derivative(alpha)),c_2*fabs(phi.first_derivative(0.0)));

   return decr_cond && curv_cond;
}

} /* namespace optim */
} /* namespace numeric */
} /* namespace libmda */

#undef ACCURACY

#endif /* LIBMDA_WOLFE_LINE_SEARCH_H_INCLUDED */
