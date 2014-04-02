#ifndef LIBMDA_IMDA_RAND_H_INCLUDED
#define LIBMDA_IMDA_RAND_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fix to use new types at some point
#include "../IMDA.h"

#include "imda_access.h"

namespace libmda
{
namespace imda
{
namespace detail
{

//
// op_rand
//
struct op_rand
{
   template<class V, class... Is>
   static void apply(V& v, Is... is)
   {
      v.at(is...) = (Value_type<V>)rand() / RAND_MAX;
      //v.at(is...) = 1.0;
   }
};

struct rand_seed
{
   rand_seed()
   {
      srand(time(NULL));
      //srand(400);
   }
};

void seed();

} /* namespace detail */

//
// imda_rand: fill mda with random numbers
//
//srand (time(NULL));

template<class A>
void imda_rand(IMDAAccessComb<A>& mda)
{
   // seed rand
   // NB MAKE OWN RNG AT SOME POINT !
   detail::seed();
   util::for_loop_expand<detail::op_rand>::apply(mda);
}

template<class A>
void imda_rand(access_combined<A>& mda)
{
   // seed rand
   // NB MAKE OWN RNG AT SOME POINT !
   detail::seed();
   util::for_loop_expand<detail::op_rand>::apply(mda);
}

} /* namespace imda */
} /* namespace libmda */

#endif /* LIBMDA_IMDA_RAND_H_INCLUDED */
