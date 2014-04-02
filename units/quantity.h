#ifndef LIBMDA_QUANTITY_H_INCLUDED
#define LIBMDA_QUANTITY_H_INCLUDED

#include <iostream>
#include "unit.h"

namespace libmda
{
namespace units
{

//
// template class that has a UnitVec as template 
//
template<class U, class T = double>
class quantity_
{
   public:
      explicit constexpr quantity_(T d): m_raw_data(d) 
      { 
      }
      
      T& val()       
      { 
         return m_raw_data; 
      }

      T const& val() const 
      { 
         return m_raw_data; 
      }
      
      //constexpr typename unit_to_string<u>::type unit() const 
      //{ return typename unit_to_string<u>::type(); }
   
   private:
      T m_raw_data;
};

//
// interface
//
template<class... Us>
using quantity=quantity_< makeUnit<Us...> >;

//
// ostream output
//
template<class U, class T>
std::ostream& operator<<(std::ostream& a_stream, const quantity_<U,T>& q)
{ 
   a_stream << q.val(); 
   return a_stream; 
}

//
// construction wrapper
//
template<class... U, class T>
constexpr quantity<U...> make_quantity(const T val)
{ 
   return quantity<U...>(val); 
}

} // namespace units
} // namespace libmda

#endif /* LIBMDA_QUANTITY_H_INCLUDED */
