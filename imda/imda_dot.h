#ifndef LIBMDA_IMDA_DOT_H_INCLUDED
#define LIBMDA_IMDA_DOT_H_INCLUDED

// NB FIX TO USE NEW TYPES !
#include "../IMDA.h"

namespace libmda
{
namespace imda
{
namespace detail
{

struct op_dot
{
   template<class V, class U, typename... ints>
   static void apply(const V& v, const U& u, Value_type<V>& res, const ints... i)
   {
      res += v.at(i...)*u.at(i...);
   }
};

} /* namespace detail */

//
// imda_dot
//
template<class A, class B>
Value_type<A> imda_dot(const IMDAAccessComb<A>& mda1, const IMDAAccessComb<B>& mda2)
{
   Value_type<A> result = 0;
   util::for_loop_expand<op_dot>::apply(mda1,mda2,result);
   return result;
}

template<class A, class B>
inline Value_type<A> dot(const IMDAAccessComb<A>& mda1, const IMDAAccessComb<B>& mda2)
{
   return imda_dot(mda1,mda2);
}

} // imda
} // libmda

#endif /* LIBMDA_IMDA_DOT_H_INCLUDED */
