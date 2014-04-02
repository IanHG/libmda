#ifndef LIBMDA_IMDA_ZERO_H_INCLUDED
#define LIBMDA_IMDA_ZERO_H_INCLUDED

#include "../IMDA.h"
#include "imda_access.h"

namespace libmda
{
namespace imda
{
namespace detail
{
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

} /* namespace detail */

template<class A>
void imda_zero(IMDAAccessComb<A>& mda)
{
   util::for_loop_expand<op_zero>::apply(mda);
}

template<class A>
void imda_zero(access_combined<A>& mda)
{
   util::for_loop_expand<op_zero>::apply(mda);
}

} /* namespace imda */
} /* namespace libmda */

#endif /* LIBMDA_IMDA_ZERO_H_INCLUDED */
