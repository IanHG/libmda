#ifndef LIMBDA_META_BINARY_PREDICATES_H_INCLUDED
#define LIMBDA_META_BINARY_PREDICATES_H_INCLUDED

#include "val.h"

namespace libmda
{
namespace meta
{

//
//
//
struct value_less_than
{
   template<class T, class U>
   struct apply: detail::val<bool, (T::value < U::value)>
   {
   };
};

//
// 
//
struct value_greater_than
{  
   template<class T, class U>
   struct apply: detail::val<bool, (T::value > U::value)>
   {
   };
};

} /* namespace meta */
} /* namespace libmda */

#endif /* LIMBDA_META_BINARY_PREDICATES_H_INCLUDED */
