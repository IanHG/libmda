#ifndef LIBMDA_METAPROG_FIND_POSITIONS_H
#define LIBMDA_METAPROG_FIND_POSITIONS_H

#include "../meta/std_wrappers.h"
#include "../meta/iterator.h"
#include "../meta/empty.h"

namespace libmda
{
namespace meta
{
namespace detail
{
template<class tuple1, class B, class E, class Res>
struct find_positions_impl:
   find_positions_impl<tuple1, next<B>, E, push_back<Res,pos<find<tuple1,deref<B> > > > >
{ };
template<class tuple1, class E, class Res>
struct find_positions_impl<tuple1,E,E,Res>
{ using type = Res; };

// find the positions of tuple2's elements in tuple1
template<class tuple1, class tuple2>
struct find_positions_: find_positions_impl<tuple1, begin<tuple2>, end<tuple2>, empty<tuple1> >
{ };
} // namespace detail

template<class tuple1, class tuple2>
using find_positions = typename detail::find_positions_<tuple1,tuple2>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_FIND_POSITIONS_H */
