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

/**********************************/
/* quantity_ operator+= quantity_ */
/**********************************/
template<class U_A, class T>
quantity_<U_A,T>& operator+=(quantity_<U_A,T>& a_lhs, const quantity_<U_A,T>& a_rhs)
{ 
   a_lhs.val() += a_rhs.val();
   return a_lhs;
}


/*********************************/
/* quantity_ operator+ quantity_ */
/*********************************/
template<class U_A, class T>
quantity_<U_A,T> operator+(const quantity_<U_A,T> a_lhs, const quantity_<U_A,T> a_rhs)
{ 
   return quantity_<U_A,T>(a_lhs.val()+a_rhs.val()); 
}

/*********************************/
/* quantity_ operator- quantity_ */
/*********************************/
template<class U_A, class T>
quantity_<U_A,T> operator-(const quantity_<U_A,T> a_lhs, const quantity_<U_A,T> a_rhs)
{ 
   return quantity_<U_A,T>(a_lhs.val()-a_rhs.val()); 
}

/*********************************/
/* quantity_ operator* quantity_ */
/*********************************/
//template<class u_L, class u_R, class u_A = UnitVecPlus<u_L,u_R> >
template<class U_L, class U_R, class T, class U_A = UnitPlus<U_L,U_R> >
quantity_<U_A,T> operator*(const quantity_<U_L,T> a_lhs, const quantity_<U_R,T> a_rhs)
{ 
   return quantity_<U_A,T>(a_lhs.val()*a_rhs.val()); 
}

/*********************************/
/* quantity_ operator/ quantity_ */
/*********************************/
//template<class u_L, class u_R, class u_S = UnitVecMinus<u_L,u_R> >
template<class U_L, class U_R, class T, class U_S = UnitMinus<U_L,U_R> >
quantity_<U_S,T> operator/(const quantity_<U_L,T> a_lhs, const quantity_<U_R,T> a_rhs)
{ 
   return quantity_<U_S,T>(a_lhs.val()/a_rhs.val()); 
}

/******************************/
/* double operator* quantity_ */
/******************************/
template<class U_A, class T>
quantity_<U_A,T> operator*(const T d, const quantity_<U_A,T> a_rhs)
{ 
   return quantity_<U_A,T>(d*a_rhs.val()); 
}

/******************************/
/* quantity_ operator* double */
/******************************/
template<class U_A, class T>
quantity_<U_A,T> operator*(const quantity_<U_A,T> a_lhs, const T d)
{ 
   return quantity_<U_A,T>(a_lhs.val()*d); 
}

/******************************/
/* double operator/ quantity_ */
/******************************/
//template<class u_A, class u_I = UnitVecInvert<u_A> >
template<class U_A, class T, class U_I = UnitInvert<U_A> >
quantity_<U_I,T> operator/(const T d, const quantity_<U_A,T> a_rhs)
{ 
   return quantity_<U_I,T>(d/a_rhs.val()); 
}

/******************************/
/* quantity_ operator/ double */
/******************************/
template<class U_A, class T>
quantity_<U_A,T> operator/(const quantity_<U_A,T> a_lhs, const T d)
{ 
   return quantity_<U_A,T>(a_lhs.val()/d); 
}

} // namespace operators
} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNITS_OPERATORS_H */
