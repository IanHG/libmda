#ifndef LIBMDA_QUANTITY_H
#define LIBMDA_QUANTITY_H

#include <iostream>

#include "unit.h"

namespace libmda
{
namespace units
{
/* template class that has a UnitVec as template */
template<class u>
class quantity_
{
   private:
      double m_raw_data;
   
   public:
      explicit constexpr quantity_(double d): m_raw_data(d) { }
      
      double&       val()       { return m_raw_data; }
      double const& val() const { return m_raw_data; }
      
      //constexpr typename unit_to_string<u>::type unit() const 
      //{ return typename unit_to_string<u>::type(); }
};

// interface
//template<class... U>
//using quantity=quantity_< typename make_UnitVec<U...>::type >;
template<class... U>
using quantity=quantity_< makeUnit<U...> >;

template<class u>
std::ostream& operator<<(std::ostream& a_stream, const quantity_<u>& q)
{ a_stream << q.val(); return a_stream; }

template<class... U>
constexpr quantity<U...> make_quantity(const double val)
{ return quantity<U...>(val); }

} // namespace units
} // namespace libmda

#endif /* LIBMDA_QUANTITY_H */
