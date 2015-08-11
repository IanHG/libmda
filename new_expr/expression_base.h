#ifndef EXPRESSIONBASE_H_INCLUDED
#define EXPRESSIONBASE_H_INCLUDED

namespace libmda
{
namespace expr
{

struct scalar_tag {};
struct mda_tag {};
 
template<class A>
struct expression_base
{
   public:
      using expression_type = A;

   protected:
      expression_base() = default;
      ~expression_base() {};

   private:
      expression_base(const expression_base<A>&) = delete;
      expression_base<A>& operator=(const expression_base<A>&) = delete;
};




} /* namespace expr */
} /* namespace libmda */

#endif /* EXPRESSIONBASE_H_INCLUDED */
