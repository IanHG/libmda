#ifndef LIBMDA_CHECK_CINDICIES_H_INCLUDED
#define LIBMDA_CHECK_CINDICIES_H_INCLUDED

#include "cindex.h"

namespace libmda
{
namespace char_expr
{
/******************************/
// helper struct to check character indicies
/******************************/
template<typename... T>
struct check_cindicies_;

template<>
struct check_cindicies_<>
{
   static const bool value = true;
};

template<typename Head, typename... Tail>
struct check_cindicies_<Head,Tail...>
{
   static const bool value = false;
};

template<char c, typename... Tail>
struct check_cindicies_<cindex<c> ,Tail...>
{
   static const bool value = true && check_cindicies_<Tail...>::value;
};

} // namespace char_expr
} // namespace libmda
#endif  /* LIBMDA_CHECK_CINDICIES_H_INCLUDED */
