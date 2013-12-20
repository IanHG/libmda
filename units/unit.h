/**
 * unit.h 
 *
 * file with functions for constructing and manipulating Units and UnitVecs
 *
 * NB: file is a bit of a mess as of now :(... fix at some point
 *
 *
 ****/
#ifndef LIBMDA_UNITS_UNIT_H
#define LIBMDA_UNITS_UNIT_H

#include"../metaprog/std_wrappers.h"
#include"../basic_using.h"

namespace libmda
{
namespace units
{
/***************************************************************************
 * class Unit: holds both unit system and unit_vec, for use with quantity_ *
 ***************************************************************************/
template<class S, class U>
struct Unit
{
   using system   = S;
   using unit_vec = U;
};

template<class U>
using Unit_system = typename U::system;
template<class U>
using Unit_vec    = typename U::unit_vec;

struct no_system { enum units{ num_units}; }; // no unit system given

/******************************************************************************/
/* wrapper for constructing basic units (unit_) and derived units (der_unit_) */
/******************************************************************************/
// helpers
template<class...> struct Is_same_system;
template<class U1, class... U> struct Is_same_system<U1,U...>
{ static const bool value = All(Is_same<typename U1::s,typename U::s>()...); };
template<class U> struct Is_same_system<U> { static const bool value = true; };
template<> struct Is_same_system<>         { static const bool value = true; };

template<class...> struct Get_system;
template<class U1, class... U> struct Get_system<U1,U...>
{ using system = typename U1::s; };
template<> struct Get_system<> { using system = no_system; };
// helpers end

template<int U, int E, int N, class S>
struct unit_ { enum{ u=U, e=E, n=N }; using s=S; };

template<class... U>
struct der_unit_ 
{ 
   static_assert(Is_same_system<U...>::value,"not same system!");
   using s = Unit_system<Get_system<U...> >;
};

/***************************************************************************/
/* class UnitVec_ holds and exponent for each unit numbered from unit emun */
/***************************************************************************/
namespace detail
{
template<int...>
struct UnitVec_ { };
} // namespace detail

/************************************************************/
/* make_UnitVec_ implementation for creating UnitVec_ types */
/************************************************************/
namespace detail
{
template<int U, int E, int N, int M, class T>
struct make_UnitVec_;

template<int I, int E, int N, int M, int... U>
struct make_UnitVec_<I, E, N, M, UnitVec_<U...> >
{
   typedef typename make_UnitVec_<I,E,N+1,M,UnitVec_<U...,0> >::type type;
};

template<int I, int E, int M,int... U>
struct make_UnitVec_<I,E,I,M,UnitVec_<U...> >
{
   typedef typename make_UnitVec_<I,E,I+1,M,UnitVec_<U...,E> >::type type;
};

template<int I, int E, int M, int... U>
struct make_UnitVec_<I,E,M,M,UnitVec_<U...> >
{
   typedef UnitVec_<U...> type;
};
} // namespace detail

/*******************************************/
/* unit plus sums U1 and U2 and returns U3 */
/*******************************************/
namespace detail
{
template<class U1, class U2, class U3>
struct UnitVecPlus_;

template<int I1, int...U1, int I2, int... U2, int... U3> 
struct UnitVecPlus_<UnitVec_<I1,U1...>,UnitVec_<I2,U2...>,UnitVec_<U3...>>
{
   typedef typename UnitVecPlus_<UnitVec_<U1...>,UnitVec_<U2...>,UnitVec_<U3...,I1+I2>>::type type;
};

template<int... U>
struct UnitVecPlus_<UnitVec_<>,UnitVec_<>,UnitVec_<U...> >
{
   typedef UnitVec_<U...> type;
};

template<class U1, class U2>
using UnitVecPlus = typename detail::UnitVecPlus_<U1,U2,UnitVec_<> >::type;

template<class U1, class U2>
struct UnitPlus_
{
   static_assert(metaprog::Is_same<Unit_system<U1>,Unit_system<U2> >(),"not same system");
   using type = Unit<Unit_system<U1>,UnitVecPlus<Unit_vec<U1>,Unit_vec<U2> > >;
};

} // namespace detail
// unit plus interface
template<class U1, class U2>
using UnitPlus = Type<detail::UnitPlus_<U1,U2> >;

/*************************************************/
/* Unit minus subtracts U1 and U2 and returns U3 */
/*************************************************/
namespace detail
{
template<class U1, class U2, class U3>
struct UnitVecMinus_;

template<int I1, int...U1, int I2, int... U2, int... U3> 
struct UnitVecMinus_<UnitVec_<I1,U1...>,UnitVec_<I2,U2...>,UnitVec_<U3...> >
{
   typedef typename UnitVecMinus_<UnitVec_<U1...>,UnitVec_<U2...>,UnitVec_<U3...,I1-I2> >::type type;
};

template<int... U>
struct UnitVecMinus_<UnitVec_<>,UnitVec_<>,UnitVec_<U...> >
{
   typedef UnitVec_<U...> type;
};

template<class U1, class U2>
using UnitVecMinus = Type<UnitVecMinus_<U1,U2,UnitVec_<> > >;

template<class U1, class U2>
struct UnitMinus_
{
   static_assert(Is_same<Unit_system<U1>,Unit_system<U2> >(),"not same system");
   using type = Unit<Unit_system<U1>,UnitVecMinus<Unit_vec<U1>,Unit_vec<U2> > >;
};
} // namespace detail
// unit minus interface
template<class U1, class U2>
using UnitMinus = Type<detail::UnitMinus_<U1,U2> >;

/************************************************************************/
/* make_UnitVec for making UnitVec_ types from unit_ or der_unit_ types */
/************************************************************************/ 
namespace detail
{
template<class...>
struct make_UnitVec;

template<class... U>
struct make_UnitVec<der_unit_<U...> > // specialization for derived unit types
{
   typedef typename make_UnitVec<U...>::type type;
};

template<class U1, class... U>
struct make_UnitVec<U1,U...>
{
   using type = UnitVecPlus<typename make_UnitVec<U1>::type,typename make_UnitVec<U...>::type>;
};

template<class U>
struct make_UnitVec<U>
{
   typedef typename make_UnitVec_<U::u,U::e,0,U::n, UnitVec_<> >::type type;
};

template<class... U>
struct makeUnit_
{
   using type = Unit<Unit_system<Get_system<U...> >,Type<make_UnitVec<U...> > >;
};
} // namespace detail
// name unit interface
template<class... U>
using makeUnit = Type<detail::makeUnit_<U...> >;

/*******************/
/* Invert unit vec */
/*******************/
namespace detail
{
template<class U1, class U2>
struct invert_UnitVec_;

template<int I1, int... U1, int... U2>
struct invert_UnitVec_<UnitVec_<I1,U1...>, UnitVec_<U2...> >
{
   typedef typename invert_UnitVec_<UnitVec_<U1...>, UnitVec_<U2...,-I1> >::type type;
};

template<int... U>
struct invert_UnitVec_<UnitVec_<>, UnitVec_<U...> >
{
   typedef UnitVec_<U...> type;
};

template<class U>
using UnitVecInvert = typename detail::invert_UnitVec_<U, UnitVec_<> >::type;

template<class U>
struct UnitInvert_
{
   using type = Unit<Unit_system<U>,UnitVecInvert<Unit_vec<U> > >;
};
} // namespace detail 
// inter unit interface
using detail::UnitVecInvert;
template<class U>
using UnitInvert = Type<detail::UnitInvert_<U> >;

} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNITS_UNIT_H */
