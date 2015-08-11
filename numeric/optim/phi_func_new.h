#ifndef PHI_FUNC_H_INCLUDED
#define PHI_FUNC_H_INCLUDED

#include"../libmda/arrays/SDArray1D.h"
#include"../libmda/expr/cindex.h"

#include"libmda_interface.h"
#include"typedefs.h"
#include"result_of_aug.h"
#include"dispatch_derivatives.h"
#include"dispatch_update_solution.h"
#include"pod_functions.h"

template<class Signature> 
class phi_func;

template<class F, class Arg> 
class phi_func<F(Arg)>
{
   private:
      const F& m_f;
      Arg& m_x;
      const SDArray1D<Resul_t<F(Arg)> >& m_p;
      mutable SDArray1D<Resul_t<F(Arg)> > m_der;
      //double alpha;

      explicit phi_func() = delete;
      explicit phi_func(const phi_func&) = delete;
      phi_func& operator=(const phi_func&) = delete;
   
   public:
      mutable Resul_t<F(Arg)> alpha;
      
      using value_t = Resul_t<F(Arg)>;
      using step_t = Resul_t<F(Arg)>;
      
      template<class FF>
      explicit phi_func(FF&& f, Arg& x, const SDArray1D<Resul_t<F(Arg)> >& p):
           m_f(std::forward<F>(f))
         , m_x(x)
         , m_p(p) 
         , m_der(m_p.size())
         , alpha(0.0)
      { 
         dispatch_first_derivative(m_f,m_x,m_der);
      }

      ~phi_func()
      {
         // RECORY IDEA !
         std::cout << " destroying phi func " << std::endl;
         std::cout << " alpha = " << std::scientific << std::setprecision(20) << alpha << std::endl;
         libmda::numeric::floating_point<decltype(alpha)> fi(alpha);
         libmda::numeric::floating_point<decltype(alpha)> fizero(std::numeric_limits<decltype(alpha)>::epsilon());
         std::cout << fi.biased_bits() << std::endl;
         std::cout << fizero.biased_bits() << std::endl;
         if(libmda::numeric::float_eq_zero(alpha,2))
         {
            std::cout << " ALPHA IS ZERO... I'LL TRY TO RECOVER " << std::endl;
            dispatch_update_solution(m_x,0.25*m_p);
         }
      }
      
      /////
      // evaluate phi_func
      //
      ////
      auto operator()(Resul_t<F(Arg)> a) const 
         //-> decltype(std::declval<F>()(std::declval<Arg>()))
         -> double
      {
         alpha = a - alpha;
         if(!libmda::numeric::float_eq(alpha,0.0,10))
            dispatch_update_solution(m_x,alpha*m_p);
         
         alpha = a;
         double res; // fix
         invoke_evaluate(m_f,m_x,res);
         return res;
      }
      
      /////
      // first derivative of phi func
      //
      ////
      auto first_derivative(Resul_t<F(Arg)> a) const 
         -> decltype(dot(m_der,m_p))
      {
         alpha = a - alpha;
         if(!libmda::numeric::float_eq(alpha,0.0,10))
         {
            //std::cout << " HERE !! " << std::endl;
            dispatch_update_solution(m_x,alpha*m_p);
            //std::cout << " HERE 2 !! " << std::endl;
            dispatch_first_derivative(m_f,m_x,m_der);
            //std::cout << " HERE 3 !! " << std::endl;
         }
         alpha = a;
         //std::cout << " M_DER: " << m_der << std::endl;
         //std::cout << " M_P: " << m_p << std::endl;
         return dot(m_der,m_p);
      }

};

#endif /* PHI_FUNC_H_INCLUDED */
