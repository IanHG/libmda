#ifndef LIBMDA_METAPROG_SAME_AS_H
#define LIBMDA_METAPROG_SAME_AS_H

#include "../meta/std_wrappers.h"

namespace libmda
{
namespace meta
{

template<class T> struct same_as
{
   template<class U> struct apply
   {
      static const bool value = Is_same<T,U>();
   };
};

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_SAME_AS_H */
