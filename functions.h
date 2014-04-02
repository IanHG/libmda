#ifndef LIBMDA_FUNCTIONS_H_INCLUDED
#define LIBMDA_FUNCTIONS_H_INCLUDED

#include "IMDA.h"
#include "basic_using.h"

namespace libmda
{

template<class A, class B>
void MDACopy(IMDAAccess<true,A>& mda1, const IMDAAccessComb<B>& mda2)
{
   util::for_loop_expand<op_equal>::apply(mda1,mda2);
}

struct op_dot
{
   template<class V, class U, typename... ints>
   static void apply(const V& v, const U& u, Value_type<V>& res, const ints... i)
   {
      res += v.at(i...)*u.at(i...);
   }
};

//
// imda_dot
//
template<class A, class B>
Value_type<A> mda_dot(const IMDAAccessComb<A>& mda1, const IMDAAccessComb<B>& mda2)
{
   Value_type<A> result = 0;
   util::for_loop_expand<op_dot>::apply(mda1,mda2,result);
   return result;
}

//
// imda_norm
//
template<class A>
Value_type<A> mda_norm(const IMDAAccessComb<A>& mda)
{
   return ::sqrt(mda_dot(mda,mda));
}

double mda_norm(const double arg)
{
   return ::sqrt(arg*arg);
}

//
// zero
//
struct op_zero
{
   template<class V, class... Is>
   static void apply(V& v, Is... is)
   {
      v.at(is...) = Value_type<V>{0};
   }
};

} // namespace libmda

#endif /* LIBMDA_FUNCTIONS_H_INCLUDED */
