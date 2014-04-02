#ifndef LIBMDA_IMDA_NORMALIZE_H_INCLUDED
#define LIBMDA_IMDA_NORMALIZE_H_INCLUDED


// fix to use new types at some point
#include "../IMDA.h"

#include "imda_norm.h"

namespace libmda
{
namespace imda
{
namespace detail
{

//
// op_rand
//
struct op_normalize
{
   template<class V, class T, class... Is>
   static void apply(V& v, const T& t, Is... is)
   {
      v.at(is...) /= t;
   }
};

} /* namespace detail */

//
// imda_rand: fill mda with random numbers
//
template<class A>
void imda_normalize(IMDAAccessComb<A>& mda)
{
   auto norm = imda_norm(mda);
   util::for_loop_expand<detail::op_normalize>::apply(mda,norm);
}

} /* namespace imda */
} /* namespace libmda */

#endif /* LIBMDA_IMDA_NORMALIZE_H_INCLUDED */
