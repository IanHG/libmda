#ifndef LIBMDA_RTE_ABSTRACT_EXPRESSION_H_INCLUDED
#define LIBMDA_RTE_ABSTRACT_EXPRESSION_H_INCLUDED

#include <memory>
#include <cassert>

#include "../util/non_copyable.h"

namespace libmda
{
namespace rte
{

template<class T>
class abstract_expression: public util::non_copyable {
   public:
      virtual T evaluate() const = 0;
      virtual abstract_expression* clone() const = 0;
      virtual ~abstract_expression() = default;
      abstract_expression() = default;
};

/////////////////////////////////////////////////////////////////////
//
// terminal expressions
//
/////////////////////////////////////////////////////////////////////
template<class T>
class terminal_expression: public abstract_expression<T> {
   public:
      virtual ~terminal_expression() = default;
};

//==================================================================
// literal expression
//==================================================================
template<class T>
class literal_expression: public terminal_expression<T> {
   public:
      literal_expression(const T& a_literal): m_literal(a_literal) { }
      ~literal_expression() = default;

      T evaluate() const { return m_literal; }
      literal_expression* clone() const { return new literal_expression(m_literal); }
   private:
      const T m_literal;
};

template<class T>
inline literal_expression<T>* make_literal_expression(T&& t)
{
   return new literal_expression<T>(std::forward<T>(t));
}

//==================================================================
// variable expression
//==================================================================
template<class T>
class variable_expression: public terminal_expression<T> {
   public:
      variable_expression(int a_poss): m_poss(a_poss) { }
      ~variable_expression() = default;
      
      variable_expression* clone() const { return new variable_expression(m_poss); }
      const T& evaluate() const { return T(m_poss); }
   private:
      T& m_variable;
      int m_poss;
};

/////////////////////////////////////////////////////////////////////
//
// non terminal expressions
//
/////////////////////////////////////////////////////////////////////
template<class T>
class non_terminal_expression: public abstract_expression<T> {
   public:
      virtual ~non_terminal_expression() = default;
};

/////////////////////////////////////////////////////////////////////
// unary expressions
/////////////////////////////////////////////////////////////////////
template<class T>
class unary_expression: public non_terminal_expression<T> {
   public:
      virtual ~unary_expression() = default;
   protected:
      const std::unique_ptr<const abstract_expression<T> > m_expr;
};

/////////////////////////////////////////////////////////////////////
// binary expressions
/////////////////////////////////////////////////////////////////////
template<class T1, class T2 = T1, class T3 = T1>
class binary_expression: public non_terminal_expression<T3> {
   public:
      binary_expression(abstract_expression<T1>* a_lhs_expr
                      , abstract_expression<T2>* a_rhs_expr
                      ) 
         : 
           m_lhs_expr(a_lhs_expr)
         , m_rhs_expr(a_rhs_expr)
      { 
      }

      virtual ~binary_expression() = default;
   protected:
      const std::unique_ptr<const abstract_expression<T1> > m_lhs_expr;
      const std::unique_ptr<const abstract_expression<T2> > m_rhs_expr;
};

template<class T> struct expression_trait;

//==================================================================
// sum expression
//==================================================================
template<class T1, class T2> class sum_expression;
template<class T1, class T2> struct expression_trait<sum_expression<T1,T2> > {
   using type = decltype(std::declval<T1>() + std::declval<T2>());
};

template<class T1, class T2>
class sum_expression: public binary_expression<T1,T2,typename expression_trait<sum_expression<T1,T2> >::type> {
   using return_type = typename expression_trait<sum_expression<T1,T2> >::type;
   public:
      sum_expression(abstract_expression<T1>* a_lhs_expr
                   , abstract_expression<T2>* a_rhs_expr
                   )
         :
           binary_expression<T1,T2,return_type>(a_lhs_expr, a_rhs_expr)  
      { 
      }
      
      sum_expression<T1,T2>* clone() const { assert(false); return nullptr; }
      return_type evaluate() const { return this->m_lhs_expr->evaluate() + this->m_rhs_expr->evaluate(); }
   private:
};

template<class T1, class T2>
inline sum_expression<T1,T2>* make_sum_expression(abstract_expression<T1>* expr1
                                                , abstract_expression<T2>* expr2
                                                ) 
{
   return new sum_expression<T1,T2>(expr1,expr2);
}

/////////////////////////////////////////////////////////////////////
// n-ary expressions
/////////////////////////////////////////////////////////////////////

} /* namespace rte */
} /* namespace libmda */

#endif /* LIBMDA_RTE_ABSTRACT_EXPRESSION_H_INCLUDED */
