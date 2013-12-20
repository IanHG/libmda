#ifndef LIBMDA_UNITS_OPERATORS_H
#define LIBMDA_UNITS_OPERATORS_H

#include "quantity.h"
#include "unit.h"

namespace libmda
{
namespace units
{
namespace operators
{

/*********************************/
/* quantity_ operator+ quantity_ */
/*********************************/
template<class u_A>
quantity_<u_A> operator+(const quantity_<u_A> a_lhs, const quantity_<u_A> a_rhs)
{ return quantity_<u_A>(a_lhs.val()+a_rhs.val()); }

/*********************************/
/* quantity_ operator- quantity_ */
/*********************************/
template<class u_A>
quantity_<u_A> operator-(const quantity_<u_A> a_lhs, const quantity_<u_A> a_rhs)
{ return quantity_<u_A>(a_lhs.val()-a_rhs.val()); }

/*********************************/
/* quantity_ operator* quantity_ */
/*********************************/
//template<class u_L, class u_R, class u_A = UnitVecPlus<u_L,u_R> >
template<class u_L, class u_R, class u_A = UnitPlus<u_L,u_R> >
quantity_<u_A> operator*(const quantity_<u_L> a_lhs, const quantity_<u_R> a_rhs)
{ return quantity_<u_A>(a_lhs.val()*a_rhs.val()); }

/*********************************/
/* quantity_ operator/ quantity_ */
/*********************************/
//template<class u_L, class u_R, class u_S = UnitVecMinus<u_L,u_R> >
template<class u_L, class u_R, class u_S = UnitMinus<u_L,u_R> >
quantity_<u_S> operator/(const quantity_<u_L> a_lhs, const quantity_<u_R> a_rhs)
{ return quantity_<u_S>(a_lhs.val()/a_rhs.val()); }

/******************************/
/* double operator* quantity_ */
/******************************/
template<class u_A>
quantity_<u_A> operator*(const double d, const quantity_<u_A> a_rhs)
{ return quantity_<u_A>(d*a_rhs.val()); }

/******************************/
/* quantity_ operator* double */
/******************************/
template<class u_A>
quantity_<u_A> operator*(const quantity_<u_A> a_lhs, const double d)
{ return quantity_<u_A>(a_lhs.val()*d); }

/******************************/
/* double operator/ quantity_ */
/******************************/
//template<class u_A, class u_I = UnitVecInvert<u_A> >
template<class u_A, class u_I = UnitInvert<u_A> >
quantity_<u_I> operator/(const double d, const quantity_<u_A> a_rhs)
{ return quantity_<u_I>(d/a_rhs.val()); }

/******************************/
/* quantity_ operator/ double */
/******************************/
template<class u_A>
quantity_<u_A> operator/(const quantity_<u_A> a_lhs, const double d)
{ return quantity_<u_A>(a_lhs.val()/d); }

} // namespace operators
} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNITS_OPERATORS_H */
