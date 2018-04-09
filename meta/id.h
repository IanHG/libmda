#ifndef LIBMDA_META_ID_H_INCLUDED
#define LIBMDA_META_ID_H_INCLUDED

namespace libmda
{
namespace meta
{
namespace detail
{

//
//
//
template<class T>
struct id
{
   using type = T;
};

} /* namespace detail */
} /* namespace meta */
} /* namespace libmda */

#endif /* LIBMDA_META_ID_H_INCLUDED */
