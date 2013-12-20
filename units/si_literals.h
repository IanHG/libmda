#ifndef LIBMDA_LITERALS_H
#define LIBMDA_LITERALS_H

#include "quantity.h"
#include "si_unit.h"

namespace libmda
{
namespace units
{
namespace si
{

#define CREATE_SIMPLE_LITERAL(LITERAL) \
constexpr quantity< LITERAL<1> > \
operator"" _##LITERAL(long double d) \
{ return quantity< LITERAL<1> >(d); }

// si base units
CREATE_SIMPLE_LITERAL(kg) //kilograms
CREATE_SIMPLE_LITERAL(m ) //meters
CREATE_SIMPLE_LITERAL(s ) //seconds
CREATE_SIMPLE_LITERAL(A ) //amperre
CREATE_SIMPLE_LITERAL(K ) //Kelvin
CREATE_SIMPLE_LITERAL(mol) //mol
CREATE_SIMPLE_LITERAL(cd) //candela

// si derived units
CREATE_SIMPLE_LITERAL(rad)  //radians
CREATE_SIMPLE_LITERAL(sr)  //ste-radians
CREATE_SIMPLE_LITERAL(N)  //newton
CREATE_SIMPLE_LITERAL(Hz)  //hertz
CREATE_SIMPLE_LITERAL(Pa)  //Pascal
CREATE_SIMPLE_LITERAL(J)  //Joule
CREATE_SIMPLE_LITERAL(W)  //Watt
CREATE_SIMPLE_LITERAL(C)  //Coulomb
CREATE_SIMPLE_LITERAL(V)  //Volt
CREATE_SIMPLE_LITERAL(F)  //farad
CREATE_SIMPLE_LITERAL(ohm)  //ohm
CREATE_SIMPLE_LITERAL(S)  //Siemens
CREATE_SIMPLE_LITERAL(Wb)  //Weber
CREATE_SIMPLE_LITERAL(T)  //Tesla
CREATE_SIMPLE_LITERAL(H)  //Henry
CREATE_SIMPLE_LITERAL(lm)  
CREATE_SIMPLE_LITERAL(lx)  
CREATE_SIMPLE_LITERAL(Bq) // bequrel
CREATE_SIMPLE_LITERAL(Gy) // Gray
CREATE_SIMPLE_LITERAL(Sv) // Sievert
CREATE_SIMPLE_LITERAL(kat) // katar

#undef CREATE_SIMPLE_LITERAL

} // namespace literals
} // namespace units
} // namespace libmda

#endif /* LIBMDA_LITERALS_H */
