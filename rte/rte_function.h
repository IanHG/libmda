#ifndef LIBMDA_RTE_FUNCTION_H_INCLUDED
#define LIBMDA_RTE_FUNCTION_H_INCLUDED

#include "abstract_expression.h"

namespace libmda
{
namespace rte
{

template<class T>
class rte_function {
   public:
      //////
      // ctors and dtor
      //////
      rte_function() = delete;
      rte_function(const rte_function&) = delete;
      rte_function(rte_function&&) = default; // default move
      rte_function& operator=(const rte_function&) = delete;
      ~rte_function() = default;

      rte_function(abstract_expression<T>* a_expr
                 , const std::vector<std::string>& a_variables
                 )
         : 
           m_expr(a_expr)
         , m_variables(a_variables)
      {
      }

      //////
      //
      //////
      T evaluate() const { return m_expr->evaluate(); };
      const std::string& variable_string(int i) const { return m_variables[i]; }

   private:
      std::unique_ptr<const abstract_expression<T> > m_expr;
      const std::vector<std::string> m_variables;
};

template<class T>
inline rte_function<T> make_rte_function(abstract_expression<T>* expr, const std::vector<std::string>& var)
{
   return rte_function<T>(expr,var);
}

} /* namespace rte */
} /* namespace libmda */

#endif /* LIBMDA_RTE_FUNCTION_H_INCLUDED */
