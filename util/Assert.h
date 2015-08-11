#ifndef LIBMDA_UTIL_ASSERT_H_INCLUDED
#define LIBMDA_UTIL_ASSERT_H_INCLUDED

#include "../meta/std_wrappers.h"

namespace libmda
{
namespace util
{
namespace detail
{

} /* namespace detail */

template<class T>
struct Is_type
{
   template<class U>
   struct apply
   {
      static const bool value = std::is_same<T,U>::value;
   };
};

struct Is_floating_point
{
   template<class U>
   struct apply
   {
      static const bool value = std::is_floating_point<U>::value;
   };
};

template<size_t I>
struct Order_equal
{
   template<class U>
   struct apply
   {
      static const bool value = (U::order == I);
   };
};

template<class T, class Pred>
constexpr bool Assert_value_type()
{
   return Pred::template apply<typename T::value_type>::value;
}

template<class T, template<class> class Pred>
constexpr bool Assert_value_type()
{
   return Pred<typename T::value_type>::value;
}

template<class T, class Pred>
constexpr bool Assert_order()
{
   return Pred::template apply<T>::value;
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_ASSERT_H_INCLUDED */
