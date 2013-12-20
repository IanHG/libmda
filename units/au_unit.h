#ifndef LIBMDA_UNITS_AU_UNIT_H
#define LIBMDA_UNITS_AU_UNIT_H

#include "unit.h"

namespace libmda
{
namespace units
{
namespace au
{

/*****************************************************/
/* SI unit interface enum with unit number constants */
/*****************************************************/
struct au { };

//           length,mass,time,electric charge, temperature
enum au_unit { L_c, M_c, T_c, Ec_c, Te_c, num_units};

using au_empty_unit = unit_<0,0,au_unit::num_units,au>;

// AU base units
template<int E>
using  bohr = unit_<au_unit::L_c,E,au_unit::num_units,au>;
template<int E>
using  me = unit_<au_unit::M_c,E,au_unit::num_units,au>;
template<int E>
using  t_A = unit_<au_unit::T_c,E,au_unit::num_units,au>;
template<int E>
using  e = unit_<au_unit::Ec_c,E,au_unit::num_units,au>;
template<int E>
using  T_A = unit_<au_unit::Te_c,E,au_unit::num_units,au>;

// AU derived units
template<int E>
using Ha = der_unit_<me<E>, bohr<2*E>, t_A<-2*E> >; 

} // namespace au
} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNITS_AU_UNIT_H */
