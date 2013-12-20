#ifndef LIBMDA_UNITS_SI_UNIT_H
#define LIBMDA_UNITS_SI_UNIT_H

#include "unit.h"

namespace libmda
{
namespace units
{
namespace si
{

/*****************************************************/
/* SI unit interface enum with unit number constants */
/*****************************************************/
struct si { };

enum si_unit { kg_c=0, m_c, s_c, A_c, K_c, mol_c, cd_c, num_units};

// SI empty_unit
using si_empty_unit = unit_<0,0,si_unit::num_units,si>;

// SI base units
template<int E>
using kg = unit_<si_unit::kg_c,E,si_unit::num_units,si>;
template<int E>
using m = unit_<si_unit::m_c,E,si_unit::num_units,si>;
template<int E>
using s = unit_<si_unit::s_c,E,si_unit::num_units,si>;
template<int E>
using A = unit_<si_unit::A_c,E,si_unit::num_units,si>;
template<int E>
using K = unit_<si_unit::K_c,E,si_unit::num_units,si>;
// SI special base units
template<int E>
using mol = unit_<si_unit::mol_c,E,si_unit::num_units,si>;
template<int E>
using cd = unit_<si_unit::cd_c,E,si_unit::num_units,si>;

// SI derived units
template<int E>
using rad=der_unit_< si_empty_unit >; // should these be pseudo base units ?
template<int E> 
using sr =der_unit_< si_empty_unit >; // should these be pseudo base units ?
template<int E>
using N=der_unit_< kg<E>,m<E>,s<-2*E> >;
template<int E>
using Hz=der_unit_< s<-E> >;
template<int E>
using Pa=der_unit_<N<E>, m<-2*E> >;
template<int E>
using J=der_unit_<N<E>, m<E> >;
template<int E>
using W=der_unit_<J<E>, s<-E> >;
template<int E>
using C=der_unit_<s<E>, A<E> >;
template<int E>
using V=der_unit_<W<E>, A<-E> >;
template<int E>
using F=der_unit_<C<E>, V<-E> >;
template<int E>
using ohm=der_unit_<V<E>, A<-E> >;
template<int E>
using S=der_unit_<A<E>, V<-E> >;
template<int E>
using Wb=der_unit_<V<E>, s<E> >;
template<int E>
using T=der_unit_<Wb<E>, m<-2*E> >;
template<int E>
using H=der_unit_<Wb<E>, A<-E> >;
template<int E>
using lm=der_unit_<cd<E>, sr<E> >;
template<int E>
using lx=der_unit_<lm<E>, m<-2*E> >;
template<int E>
using Bq=der_unit_< s<-E> >;
template<int E>
using Gy=der_unit_< J<E>, kg<-E> >;
template<int E>
using Sv=der_unit_< J<E>, kg<-E> >;
template<int E>
using kat=der_unit_< s<-E>, mol<E> >;

} // namespace si
} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNITS_SI_UNIT_H */
