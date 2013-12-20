#ifndef LIBMDA_METAPROG_SAME_AS_H
#define LIBMDA_METAPROG_SAME_AS_H

#include "../metaprog/std_wrappers.h"

namespace libmda
{
namespace metaprog
{

template<class T> struct same_as
{
   template<class U> struct apply
   {
      static const bool value = libmda::metaprog::Is_same<T,U>();
   };
};

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_SAME_AS_H */
