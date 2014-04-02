#ifndef LIBMDA_META_PAIR_H_INCLUDED
#define LIBMDA_META_PAIR_H_INCLUDED

#include "id.h"
#include "tuple.h"

namespace libmda
{
namespace meta
{
namespace detail
{

template<class T>
struct swap_pair_impl;

template<template<class, class> class Pair, class T1, class T2>
struct swap_pair_impl<Pair<T1,T2> >: id<Pair<T2,T1> >
{
};

} /* namespace detail */

template<class T>
using swap_pair = typename detail::swap_pair_impl<T>::type;

template<class T1, class T2>
struct pair: tuple<T1,T2>
{
   using first = T1;
   using second = T2;
};

//
// output for debug
//
template<class T1, class T2>
std::ostream& operator<<(std::ostream& a_ostream, const pair<T1,T2>&)
{
   T1 t1;
   T2 t2;
   a_ostream << t1 << " " << t2;
   return a_ostream;
}

} /* namespace meta */
} /* namespace libmda */

#endif /* LIBMDA_META_PAIR_H_INCLUDED */
