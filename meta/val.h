#ifndef LIBMDA_META_VAL_H_INCLUDED
#define LIBMDA_META_VAL_H_INCLUDED

namespace libmda
{
namespace meta
{
namespace detail
{
//
//
//
template<class T, T VAL>
struct val
{
   static constexpr T value = VAL;
};

} /* namespace detail */
} /* namespace meta */
} /* namespace libmda */

#endif /* LIBMDA_META_VAL_H_INCLUDED */
