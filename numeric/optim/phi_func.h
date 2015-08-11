#ifndef PHI_FUNC_H_INCLUDED
#define PHI_FUNC_H_INCLUDED

#include "../mmv/StdVectorOperators.h"

#include"../libmda/arrays/SDArray1D.h"
#include"../libmda/expr/cindex.h"

#include"typedefs.h"
#include"result_of_aug.h"
#include"invoke_derivatives.h"
#include"pod_functions.h"

template<class Signature> 
class phi_func;

template<class F, class Arg> 
class phi_func<F(Arg)>
{
   public:
      using value_t = Resul_t<F(Arg)>;
      using step_t = Resul_t<F(Arg)>;
      
      /////
      // construct phi function
      //
      ////
      phi_func(F& f, Arg& x, Arg& p)
         : m_f(f)
         , m_x(x)
         , m_p(p) 
      { 
      }
      
      /////
      // evaluate phi_func
      //
      ////
      auto operator()(Resul_t<F(Arg)> a) const 
         -> decltype(std::declval<F>()(std::declval<Arg>()))
      {
         typename std::remove_reference<Arg>::type arg = m_x + a*m_p;
         return m_f(arg);
      }
      
      /////
      // first derivative of phi func
      //
      ////
      auto first_deriv(Resul_t<F(Arg)> a) const 
         -> decltype(dot(std::declval<Argum2_t<F(Arg)> >(),std::declval<Argum2_t<F(Arg)> >()))
      {
         Argum2_t<F(Arg)> arg = m_x + a*m_p;
         Argum2_t<F(Arg)> der = m_x; // not efficent
         invoke_first_deriv(m_f,arg,der);
         return dot(der,m_p);
      }
   
   private:
      const F&   m_f;
      const Arg& m_x;
      const Arg& m_p;
};

#endif /* PHI_FUNC_H_INCLUDED */
