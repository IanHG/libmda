#ifndef LIBMDA_IMDA_NORM_H_INCLUDED
#define LIBMDA_IMDA_NORM_H_INCLUDED

#include "../IMDA.h"

#include "imda_dot.h"

namespace libmda
{
namespace imda
{

//
// imda_norm
//
template<class A>
Value_type<A> imda_norm(const IMDAAccessComb<A>& mda)
{
   return ::sqrt(mda_dot(mda,mda));
}

double imda_norm(const double arg)
{
   return ::sqrt(arg*arg);
}

} /* namespace imda */
} /* namespace libmda */

#endif /* LIBMDA_IMDA_NORM_H_INCLUDED */
